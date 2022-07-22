


test('函数每次调用会产生新的作用域链，同一个外部函数内定义的多个嵌套函数共享一个作用域链', () => {
    function counter() {
        var n = 0;
        return {
            count: () => n++,
            reset: () => n = 0
        };
    }
    var cnt1 = counter();
    var cnt2 = counter();
    cnt1.count(); //n自增
    expect(cnt2.count()).toBe(0); //由于使用不同的作用域链,因此cnt1不会影响到cnt2
    cnt1.reset();
    expect(cnt1.count()).toBe(0); //由于reset与count共享变量n，因此这里返回0
    expect(cnt2.count()).toBe(1);
});

test('ES2015循环体每次执行都会产生一个作用域', () => {
    const funcArr1 = [];
    for (var i = 0; i < 3; ++i) {
        funcArr1.push(() => i);
    }
    const resArr1 = funcArr1.map(e => e());
    const funcArr2 = [];
    for (let i = 0; i < 3; ++i) {
        funcArr2.push(() => i);
    }
    const resArr2 = funcArr2.map(e => e());
    expect(resArr1).toEqual([3, 3, 3]);
    expect(resArr2).toEqual([0, 1, 2]);
});

test('let关键字不存在变量提升(hoist)', () => {
    expect(foo).toBeFalsy();
    expect(() => bar).toThrowError('bar is not defined');
    var foo;
    let bar;
});

test('只要区块中存在let定义，则在定义前使用变量会报错(temporal dead zone)', () => {
    var foo;
    {
        expect(typeof bar).toBe('undefined');
        expect(() => typeof foo).toThrowError('foo is not defined'); //TDZ中使用typeof依然会报错
        let foo;
    }
    expect(() => { var a = a; }).not.toThrow();
    expect(() => { let b = b; }).toThrowError('b is not defined');
});

test('es6不再需要立即执行函数表达式', () => {
    (function(){
        var foo;
    }());
    //等价于
    {
        let foo;
    }
});

test('es6允许在块级作用域中声明函数，行为类似与let',() => {
    {
        function foo(){}
    }
    expect(typeof foo).toBe('undefined');
});

test('使用const定义常量', () => {
    const PI = 3.14;
    expect(() => PI = 3.5).toThrowError('Assignment to constant variable.');
});

test('const类似于java中的final，对于Object类型的变量，仅保证内存地址不变', () => {
    const foo = {bar:0};
    foo.bar = 1;
    expect(foo.bar).toBe(1);
});

