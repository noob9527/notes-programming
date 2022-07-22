

Reflect.defineProperty(Object.prototype, 'log', {
    get: function () {
        console.log(this);
    }
});

//Reflect.get(target,name,receiver)
test('使用Reflect.get获取对象属性', () => {
    const foo = { name: 'foo' };
    const bar = { name: 'bar' };
    expect(Reflect.get(foo, 'name')).toBe('foo');
});

test('使用Reflect.get获取getter属性，允许指定receiver参数来指定this的值', () => {
    const foo = {
        _name: 'foo',
        get name() {
            return this._name;
        }
    }
    const bar = {
        _name: 'bar'
    }
    expect(Reflect.get(foo, 'name')).toBe('foo');
    expect(Reflect.get(foo, 'name', bar)).toBe('bar');
});

//Reflect.set(target,name,value,receiver)
test('使用Reflect.set设置对象属性', () => {
    const foo = { name: 'foo' };
    Reflect.set(foo, 'name', 'bar');
    expect(foo.name).toBe('bar');
});

test('使用Reflect.set获取setter属性, 允许指定receiver参数来指定this的值', () => {
    const foo = {
        _name: 'foo',
        set name(value) {
            this._name = value;
        }
    }
    const bar = {
        _name: 'bar'
    }
    Reflect.set(foo, 'name', 'newFoo');
    expect(foo._name).toBe('newFoo');
    Reflect.set(foo, 'name', 'newBar', bar);
    expect(foo._name).toBe('newFoo');
    expect(bar._name).toBe('newBar');
});

//Reflect.has(target,name)
test('Reflect.has用于取代in操作符', () => {
    const foo = { name: 'foo' };
    expect('name' in foo).toBe(true);
    expect(Reflect.has(foo, 'name')).toBe(true);
});

// Reflect.deleteProperty(target,name)
test('Reflect.deleteProperty用于取代delete操作符' +
    '删除成功或属性不存在，返回true', () => {
        const obj = {
            foo: 1,
            bar: 1
        };
        Object.defineProperty(obj, 'baz', {});
        expect(delete obj.foo).toBe(true);
        expect(delete obj.whatever).toBe(true);
        //delete 操作符在严格模式下删除失败会报错
        expect(() => delete obj.baz).toThrowError("Cannot delete property 'baz' of #<Object>");
        expect(Reflect.deleteProperty(obj, 'bar')).toBe(true);
        expect(Reflect.deleteProperty(obj, 'whatever')).toBe(true);
        //Reflect.deleteProperty删除失败返回false
        expect(Reflect.deleteProperty(obj, 'baz')).toBe(false);
    });

// Reflect.construct(target,args)
test('Reflect.construct用于取代new操作符', () => {
    function Person(name) {
        this.name = name;
    }
    expect(//注意这里使用参数数组
    Reflect.construct(Person, ['foo'])).toEqual(new Person('foo'));
});

// Reflect.getPrototypeOf(target)
test('Reflect.getPrototypeOf用于取代Object.getPrototypeOf', () => {
    const parent = {};
    const child = Object.create(parent);
    expect(Object.getPrototypeOf(child)).toBe(parent);
    expect(Reflect.getPrototypeOf(child)).toBe(parent);
    //如果第一个参数不是对象，Reflect.getPrototypeOf会报错
    expect(() => Reflect.getPrototypeOf(0)).toThrowError('Reflect.getPrototypeOf called on non-object');
    //Object.getPrototypeOf会试图将其转换为对象（装箱）
    expect(Object.getPrototypeOf(0)).toBe(Number.prototype);
    expect(() => Object.getPrototypeOf(null)).toThrowError('Cannot convert undefined or null to object');
});

// Reflect.setPrototypeOf(target, prototype)
test('Reflect.setPrototypeOf用于取代Object.setPrototypeOf', () => {
    const parent = {};
    const child1 = {};
    const child2 = {};
    const child3 = 0;
    Object.setPrototypeOf(child1, parent);
    Reflect.setPrototypeOf(child2, parent);
    expect(Reflect.getPrototypeOf(child1)).toBe(parent);
    expect(Reflect.getPrototypeOf(child2)).toBe(parent);
    //如果第一个参数不是对象,Reflect.setPrototypeOf会报错
    expect(() => Reflect.setPrototypeOf(child3, parent)).toThrowError('Reflect.setPrototypeOf called on non-object');
    //Object.setPrototypeOf会试图将其转为对象（装箱），而在操作完成后，装箱生成的对象会被丢弃，因此相当于什么都没做
    Object.setPrototypeOf(child3, parent);
    expect(Object.getPrototypeOf(child3)).toBe(Number.prototype);
});

// Reflect.apply(target,thisArg,args)
test('Reflect.apply用于取代Function.prototype.apply.call(func, thisArg, args)', () => {
    const foo = { name: 'foo' };
    function fn() {
        return this.name;
    }
    expect(fn.apply(foo)).toBe('foo');//修改this指向
    fn.apply = function () {
        return 'bar';
    }
    //现在如果要调用fn，并将this指向foo，不能直接使用fn.apply，因为它被复写了
    expect(fn.apply(foo)).toBe('bar');
    expect(Function.apply.call(fn, foo)).toBe('foo');
    expect(Reflect.apply(fn, foo, [])).toBe('foo');
});

// Reflect.defineProperty(target,name,desc)
test('Reflect.defineProperty用于取代Object.defineProperty', () => {
    const foo = {};
    Reflect.defineProperty(foo, 'name', { value: 'foo' });//该属性是不可配置的
    expect(foo.name).toBe('foo');
    //使用Object.defineProperty失败会报错
    expect(() => Object.defineProperty(foo, 'name', { value: 'bar' })).toThrowError('Cannot redefine property: name');
    //使用Reflect.defineProperty失败会返回false
    expect(Reflect.defineProperty(foo, 'name', { value: 'bar' })).toBe(false);
});

// Reflect.getOwnPropertyDescriptor(target, name)
test('Reflect.getOwnPropertyDescriptor用于取代Object.getOwnPropertyDescriptor', () => {
    const foo = {}
    Reflect.defineProperty(foo, 'name', {});
    expect(Reflect.getOwnPropertyDescriptor(foo, 'name')).toEqual({
        value: undefined,
        writable: false,
        enumerable: false,
        configurable: false
    });
    //Object会尝试将第一个参数转换为对象
    expect(Object.getOwnPropertyDescriptor(0, 'name')).toBeFalsy();
    //Reflect第一个参数不是对象则报错
    expect(() => Reflect.getOwnPropertyDescriptor(0, 'name')).toThrowError('Reflect.getOwnPropertyDescriptor called on non-object');
});

// Reflect.preventExtensions(target)
test('Reflect.preventExtensions用于取代Object.preventExtensions', () => {
    const foo = {};
    const bar = {};
    //Object.preventExtensions返回传入的参数本身
    expect(Object.preventExtensions(foo)).toBe(foo);
    expect(Object.isExtensible(foo)).toBe(false);
    expect(Object.preventExtensions(0)).toBe(0);
    //Reflect.preventExtensions返回布尔值，参数不合法则报错
    expect(Reflect.preventExtensions(bar)).toBe(true);
    expect(Reflect.isExtensible(foo)).toBe(false);
    expect(() => Reflect.preventExtensions(0)).toThrowError('Reflect.preventExtensions called on non-object');
});

// Reflect.isExtensible(target)
test('Reflect.isExtensible用于取代Object.isExtensible', () => {
    expect(Object.isExtensible(0)).toBe(false);
    expect(() => Reflect.isExtensible(0)).toThrowError('Reflect.isExtensible called on non-object');
});

// Reflect.ownKeys(target)
test('Reflect.ownKeys返回对象的所有属性', () => {
    const obj = {
        foo:0,
        [Symbol.for('foo')]:0
    }
    Object.defineProperties(obj, {
        bar:{
            value:0
        },
        [Symbol.for('bar')]:{
            value:0
        }
    });
    //基本等同于Object.getOwnPropertyNames与Object.getOwnPropertySymbols之和
    expect(Reflect.ownKeys(obj)).toEqual(['foo','bar',Symbol.for('foo'), Symbol.for('bar')]);
});
