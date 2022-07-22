


//object直接量
test('直接量简写', () => {
    const foo = 'foo';
    const obj = {
        //属性
        foo,
        //方法
        bar() {
            return 'bar';
        },
        //generator函数
        *gen() {
            yield 'gen';
        }
    }
    expect(obj.foo).toBe('foo');
    expect(obj.bar()).toBe('bar');
    expect(obj.gen().next().value).toBe('gen');
});

test('在直接量中使用表达式', () => {
    const bar = 'bar';
    const obj = {
        ['f' + 'oo']: 'foo',
        [bar]: 'bar',
        ['say' + 'Hi']() {
            return 'hello';
        }
    }
    expect(obj.foo).toBe('foo');
    expect(obj.bar).toBe('bar');
    expect(obj.sayHi()).toBe('hello');
});

//Object新的静态方法
//Object.is
test('使用Object.is方法判等', () => {
    expect(+0 === -0).toBe(true);
    expect(Object.is(+0, -0)).toBe(false);
    expect(NaN === NaN).toBe(false);
    expect(Object.is(NaN, NaN)).toBe(true);
});

//Object.assign
test('Object.assign的返回值等于第一个参数', () => {
    const dest = { id: 0 };
    const src = { id: 1 };
    expect(Object.assign(dest, src)).toBe(dest);
});

test('Object.assign只复制自有可枚举属性', () => {
    const dest = { prop1: 'prop1' };
    const src = { prop2: 'prop2' };
    //继承属性
    Object.setPrototypeOf(src, { prop3: 'prop3' });
    //不可枚举属性
    Object.defineProperty(src, 'prop4', {
        value: 'prop4',
        writable: true,
        enumerable: false,
        configurable: true
    });
    Object.assign(dest, src);
    expect(dest).toEqual({
        prop1: 'prop1',
        prop2: 'prop2',
    });
});

test('如果存在同名属性,则根据参数列表中的顺序，后面的属性会覆盖前面的属性', () => {
    const dest = { id: 0 };
    const src1 = { id: 1 };
    const src2 = { id: 2 };
    Object.assign(dest, src1, src2);
    expect(dest.id).toBe(2);
});

test('可以拷贝属性名为symbol的属性', () => {
    const dest = {};
    const src = { [Symbol.for('foo')]: 'foo' };
    Object.assign(dest, src);
    expect(dest[Symbol.for('foo')]).toBe('foo');
});

test('assign实行浅拷贝', () => {
    const dest = {};
    const src = { foo: {}, bar: [] };
    Object.assign(dest, src);
    src.foo.foo = 'foo';
    src.bar[0] = 'bar';
    expect(dest.foo.foo).toBe('foo');
    expect(dest.bar[0]).toBe('bar');
});

test('assign可以用来处理数组，但会将数组视为对象', () => {
    expect(Object.assign([1, 2, 3], [4, 5])).toEqual([4, 5, 3]);
});

//Object.getOwnPropertySymbols
test('Object.getOwnPropertySymbols返回对象自身的所有symbol属性,' +
    '包含不可枚举属性', () => {
        const obj = { a: 1 };
        const proto = Object.getPrototypeOf(obj);
        Object.defineProperties(obj, {
            [Symbol.for('b')]: { value: 2 }, //不可枚举属性
        });
        proto[Symbol.for('c')] = 3;          //继承属性
        expect(Object.getOwnPropertySymbols(obj)).toEqual([Symbol.for('b')]);
    });

//Reflect.ownKeys
test('Reflect.ownKeys返回对象自身的所有属性' +
    '包含symbol属性与不可枚举属性', () => {
        const obj = { a: 1 };
        const proto = Object.getPrototypeOf(obj);
        Object.defineProperties(obj, {
            [Symbol.for('b')]: { value: 2 }, //不可枚举属性
        });
        proto[Symbol.for('c')] = 3;
        proto.d = 4;
        expect(Reflect.ownKeys(obj)).toEqual(['a', Symbol.for('b')]);
    });

//Object.setPrototypeOf(因为性能的原因，应该尽量避免使用)
test('使用Object.setPrototypeOf代替设置对象的__proto__属性', () => {
    const child = { foo: 'foo' };
    const parent = { bar: 'bar' };
    Object.setPrototypeOf(child, parent);
    expect(Object.getPrototypeOf(child)).toBe(parent);
    expect(child.bar).toBe('bar');
});

//Object.values ,Object.entries
test('Object.values返回所有对象自身的可枚举属性的值,不包括symbol属性', () => {
    const obj = {
        a: 1,
        [Symbol.for('b')]: 2
    };
    Object.defineProperties(obj, {
        c: { value: 3 } //不可枚举
    });
    Object.setPrototypeOf(obj, { d: 4 });//继承属性
    expect(Object.values(obj)).toEqual([1]);
});

test('Object.entries返回所有对象自身的可枚举属性的键值对数组，不包括symbol属性', () => {
    const obj = {
        a: 1,
        [Symbol.for('b')]: 2,
        e: 2
    };
    Object.defineProperties(obj, {
        c: { value: 3 } //不可枚举
    });
    Object.setPrototypeOf(obj, { d: 4 });//继承属性
    expect(Object.entries(obj)).toEqual([['a', 1], ['e', 2]]);
});

test('Object.entries的一个应用场景，将对象转换为Map', () => {
    const obj = { foo: 'foo', bar: 'bar' };
    const map = new Map(Object.entries(obj));
    expect(map.size).toBe(2);
    expect(map.get('foo')).toBe('foo');
    expect(map.get('bar')).toBe('bar');
});

//Object.getOwnPropertyDescriptors
test('Object.getOwnPropertyDescriptors返回对象所有自身属性的描述对象', () => {
    const obj = {};
    const fooDesc = {
        value: 'foo',
        writable: true,
        enumerable: true,
        configurable: true
    }
    const barDesc = {
        get: function () {
            return 'bar';
        },
        set: undefined
    }
    Object.defineProperties(obj, {
        foo: fooDesc,
        bar: barDesc
    });
    const objDesc = Object.getOwnPropertyDescriptors(obj);
    expect(objDesc.foo).not.toBe(fooDesc);
    expect(objDesc.foo).toEqual(fooDesc);
    expect(objDesc.bar).not.toEqual(barDesc);
    Object.assign(barDesc, {
        enumerable: false,
        configurable: false
    });
    expect(objDesc.bar).toEqual(barDesc);
});

test('Object.getOwnPropertyDescriptors的一个使用场景是替代Object.assign实现对象的浅拷贝' +
    '这样做的优势在于能够正确拷贝getter,setter', () => {
        const src = {
            _name: 'src',
            get name() {
                return this._name;
            }
        };
        let dest = Object.assign({}, src);
        //Object.assign将get属性被拷贝成了value属性
        expect(Object.getOwnPropertyDescriptor(dest, 'name')).toEqual({
            value: 'src',
            writable: true,
            enumerable: true,
            configurable: true
        });
        //使用Object.getOwnPropertyDescriptors拷贝
        dest = {};
        Object.defineProperties(dest, Object.getOwnPropertyDescriptors(src));
        expect(dest.name).toBe('src');
        dest._name = 'dest';
        expect(dest.name).toBe('dest');
    });
