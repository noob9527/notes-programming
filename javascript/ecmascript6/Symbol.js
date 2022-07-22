


test('Symbol是js中第六种数据类型', () => {
    //前5种是 undefined,String,Boolean,Number,Object
    const s = Symbol();
    expect(typeof s).toBe('symbol');
    expect(() => s.foo = 'foo').toThrow();
});

test('由于Symbol是原始数据类型，因此无法使用new操作符创建，也无法添加属性', () => {
    const s = Symbol();
    expect(() => new Symbol()).toThrowError('Symbol is not a constructor');
    expect(() => s.foo = 'foo').toThrowError("Cannot create property 'foo' on symbol 'Symbol()'");
});

test('Symbol函数可以接收一个字符串,作为该Symbol的描述', () => {
    const foo = Symbol('foo');
    //如果参数是对象，则会调用器toString方法获取字符串描述
    const bar = Symbol({
        toString() {
            return 'bar';
        }
    });
    expect(foo.toString()).toBe('Symbol(foo)');
    expect(bar.toString()).toBe('Symbol(bar)');
});

test('相同描述的Symbol值并不相等', () => {
    const [s1, s2] = [Symbol(), Symbol()];
    const [s3, s4] = [Symbol('foo'), Symbol('foo')];
    expect(s1 == s2).toBe(false);
    expect(s3 == s4).toBe(false);
});

//convert
test('Symbol值不允许隐式转换为字符串，只允许显示转换', () => {
    const foo = Symbol('foo');
    expect(String(foo)).toBe('Symbol(foo)');
    expect(foo.toString()).toBe('Symbol(foo)');
    expect(() => `${foo}`).toThrowError('Cannot convert a Symbol value to a string');
});

test('Symbol值允许隐式转换为boolean', () => {
    const s = Symbol();
    expect(!!s).toBe(true);
    expect(Boolean(s)).toBe(true);
});

test('Symbol值不允许转换为Number', () => {
    const s = Symbol();
    expect(() => Number(s)).toThrowError('Cannot convert a Symbol value to a number');
});

//symbol as key
test('symbol最标准的用法是作为对象的key,以保证属性不会被其他人覆盖' +
    '使用Symbol作为属性key,需要使用方括号赋值与访问', () => {
        const s = Symbol();
        const obj = {};
        obj.s = 'foo'; //这样赋值的属性key并不是symbol值，而是字符串s
        expect(obj[s]).toBeFalsy();
        expect(obj['s']).toBe('foo');
    });

test('Object.keys,Object.getOwnPropertyNames,JSON.stringify等方法会跳过Symbol属性', () => {
    const obj = {
        [Symbol('foo')]: 'foo',
        bar: 'bar'
    }
    expect(Object.keys(obj)).toEqual(['bar']);
    expect(Object.getOwnPropertyNames(obj)).toEqual(['bar']);
    expect(JSON.stringify(obj)).toBe('{"bar":"bar"}');
});

test('使用Object.getOwnPropertySymbols获取对象所有Symbol属性', () => {
    const obj = {
        [Symbol.for('foo')]: 'foo',
        bar: 'bar'
    }
    expect(Object.getOwnPropertySymbols(obj)).toEqual([Symbol.for('foo')]);
});

//Symbol.for,Symbol.keyFor
test('使用Symbol.for创建可重用的Symbol值', () => {
    const [s1, s2] = [Symbol('foo'), Symbol('foo')];
    const [s3, s4] = [Symbol.for('bar'), Symbol.for('bar')];
    expect(s1 == s2).toBe(false);
    expect(s3 === s4).toBe(true);
});

test('Symbol.keyFor返回已使用Symbol.for注册的symbol值的描述字符串', () => {
    const [s1, s2] = [Symbol('foo'), Symbol.for('foo')];
    expect(Symbol.keyFor(s1)).toBeFalsy();
    expect(Symbol.keyFor(s2)).toBe('foo');
});

//内置Symbol值
test('对象的Symbol.hasInstance方法,决定了instanceof运算符的执行结果', () => {
    const obj = {
        [Symbol.hasInstance](value) {
            return value === 'foo';
        }
    };
    expect('bar' instanceof obj).toBe(false);
    expect('foo' instanceof obj).toBe(true);
});

test('Symbol.toStringTag决定Object.prototype.toString的返回结果', () => {
    const obj = {
        [Symbol.toStringTag]: 'foo'
    }
    expect(obj.toString()).toBe('[object foo]');
});

test('Symbol.toPrimitive绝对该对象如何被转换成原始值', () => {
    const foo = {
        [Symbol.toPrimitive](hint) {
            switch (hint) {
                case 'number':
                    return 999;
                case 'string':
                    return 'foo';
                case 'default':
                    return 'default';
            }
        }
    }
    expect(Number(foo)).toBe(999);
    expect(String(foo)).toBe('foo');
    expect(foo == 'default').toBe(true);
});

test('Symbol.iterator,决定该对象默认的遍历器方法', () => {
    const obj = {
        *[Symbol.iterator]() {
            yield 'foo';
            yield 'bar';
            yield 'baz';
        }
    };
    expect([...obj]).toEqual(['foo','bar','baz']);
});

//Symbol.match,Symbol.replace,Symbol.search,Symbol.split
test('对象的Symbol.match决定了执行str.match(obj)的返回结果' +
    'Symbol.replace,Symbol.search,Symbol.split同理', () => {
        //String.prototype.match(regexp) 等同于 regexp[Symbol.match](this)
        const obj = {
            [Symbol.match](str) {
                return str.length;
            }
        };
        expect('foo'.match(obj)).toBe(3);
    });
