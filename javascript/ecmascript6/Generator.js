

Reflect.defineProperty(Object.prototype, 'log', {
    get: function () {
        console.log(this);
    }
});

test('如果生成器函数没有return语句，则最后一次调用返回的value值为undefined', () => {
    function* gen1() {
        yield 'foo';
    }
    function* gen2() {
        yield 'foo';
        return 'bar';
    }
    const iter1 = gen1();
    const iter2 = gen2();
    expect(iter1.next()).toEqual({ value: 'foo', done: false });
    expect(iter1.next()).toEqual({ value: undefined, done: true });
    expect(iter2.next()).toEqual({ value: 'foo', done: false });
    expect(iter2.next()).toEqual({ value: 'bar', done: true });
});

test('return语句的返回值不会被遍历到', () => {
    function* gen1() {
        yield 'foo';
    }
    function* gen2() {
        yield 'foo';
        return 'bar';
    }
    expect([...gen1()]).toEqual(['foo']);
    expect([...gen2()]).toEqual(['foo']);
});

test('普通函数调用就会执行，但生成器函数在生成的迭代器调用next时才开始执行', () => {
    let bool = false;
    function* gen() {
        bool = true;
    }
    const iter = gen();
    expect(bool).toBe(false);
    iter.next();
    expect(bool).toBe(true);
});

test('next方法第一次调用时传入的参数将被忽略', () => {
    function* generator() {
        return yield 'foo';
    }
    const iter = generator();
    expect(iter.next('whatever') //这个参数没意义
        .value).toBe('foo');
    expect(iter.next('bar')).toEqual({ value: 'bar', done: true });
});

test('生成器函数返回对象带有Symbol.iterator属性，调用该属性返回自身', () => {
    function* gen() { }
    const iter = gen();
    expect(iter[Symbol.iterator]()).toBe(iter);
});

test('生成器函数的常用场景是为对象实现遍历器接口', () => {
    const obj = {
        *[Symbol.iterator]() {
            yield* [1, 2, 3];
        }
    };
    expect([...obj]).toEqual([1, 2, 3]);
});

//Generator.prototype.throw
test('通过Generator.prototype.throw方法可以在函数体内捕获函数体外的错误', () => {
    function* gen() {
        try {
            yield;
        } catch (e) {
            expect(e.message).toBe('foo');
        }
    }
    const iter = gen();
    iter.next();
    try {
        iter.throw(new Error('foo'));
        iter.throw(new Error('bar'));
    } catch (e) {
        expect(e.message).toBe('bar');
    }
});

test('throw方法被捕获后，会自动执行一次next方法', () => {
    function* gen() {
        try {
            yield 'first';
        } catch (e) {
            expect(e.message).toBe('foo');
        }
        yield 'skip';
        yield 'bar';
    }
    const iter = gen();
    iter.next();
    iter.throw(new Error('foo'));
    expect(iter.next().value).toBe('bar');
});

//Generator.prototype.return
test('通过Generator.prototype.return方法，可以返回指定值并终止遍历器', () => {
    function* gen() {
        while (true) {
            yield 1;
        }
    }
    const iter = gen();
    expect(iter.next()).toEqual({ value: 1, done: false });
    expect(iter.return(2)).toEqual({ value: 2, done: true });
    expect(iter.next()).toEqual({ value: undefined, done: true });
});

test('如果Generator函数内部有try...finally代码块，return方法会推迟到finally代码块执行完再执行', () => {
    function* gen() {
        try {
            yield 'try';
        } finally {
            yield 'finally';
            yield 'finally';
        }
    }
    const iter = gen();
    expect(iter.next()).toEqual({ value: 'try', done: false });
    expect(iter.return('return')).toEqual({ value: 'finally', done: false });
    expect(iter.next()).toEqual({ value: 'finally', done: false });
    expect(iter.next()).toEqual({ value: 'return', done: true });
});

//yield*
test('在generator函数中直接调用另一个generator没有效果', () => {
    function* foo() {
        yield 'foo';
        bar();
    }
    function* bar() {
        yield 'bar';
    }
    const iter = foo();
    expect(iter.next()).toEqual({ value: 'foo', done: false });
    expect(iter.next()).toEqual({ value: undefined, done: true });
});

test('如果需要调用其他遍历器，可以使用for...of循环或者yield*语句', () => {
    function* foo() {
        yield 'foo';
    }
    function* bar1() {
        yield 'bar';
        for(let v of foo()){
            yield v;
        }
    }
    function* bar2(){
        yield 'bar';
        yield* foo();
    }
    const iter1 = bar1();
    const iter2 = bar2();
    expect(iter1.next()).toEqual({ value: 'bar', done: false });
    expect(iter1.next()).toEqual({ value: 'foo', done: false });
    expect(iter1.next()).toEqual({ value: undefined, done: true });
    expect(iter2.next()).toEqual({ value: 'bar', done: false });
    expect(iter2.next()).toEqual({ value: 'foo', done: false });
    expect(iter2.next()).toEqual({ value: undefined, done: true });
});

test('yield*能够遍历任何实现了iterator接口的对象',() => {
    function* gen(){
        yield '123';
        yield* '123';
    }
    const iter = gen();
    expect(iter.next().value).toEqual('123');
    expect([...iter]).toEqual(['1','2','3']);
});

test('generator函数返回的遍历器是generator函数的实例，且继承至函数的prototype', () => {
    function* gen(){};
    const iter = gen();
    gen.prototype.foo = 'foo';
    expect(iter instanceof gen).toBe(true);
    expect(iter.foo).toBe('foo');
});
