

Reflect.defineProperty(Object.prototype, 'log', {
    get: function () {
        console.log(this);
    }
});

// @decorator
// class A {}
// // 等同于
// class A {}
// A = decorator(A) || A;

test('class decorator', () => {
    @Bar
    class Foo {
        static foo = 'foo';
    }
    function Bar(target) {
        target.bar = 'bar';
    }
    expect(Foo.foo).toBe('foo');
    expect(Foo.bar).toBe('bar');
});

test('修饰器可以返回完全不同的对象', () => {
    @Bar
    class Foo {
    }
    function Bar(target) {
        return {
            bar: 'bar'
        };
    }
    expect(Foo).toEqual({ bar: 'bar' });
});

test('修饰器可以带有参数', () => {
    @Bar('super bar')
    class Foo {
        static foo = 'foo';
    }
    function Bar(bar) {
        return function (target) {
            target.bar = bar
        }
    }
    expect(Foo.foo).toBe('foo');
    expect(Foo.bar).toBe('super bar');
});

test('修饰器可以为类新增实例属性', () => {
    @Bar
    class Foo {
        foo = 'foo';
    }
    function Bar(target) {
        target.prototype.bar = 'bar';
    }
    const foo = new Foo;
    expect(foo.foo).toBe('foo');
    expect(foo.bar).toBe('bar');
});

test('修饰类的方法', () => {
    class Foo {
        @Bar
        foo() {
        }
    }

    function Bar(target, name, descriptor) {
        expect(name).toBe('foo');
        descriptor.value = 'foo';
        return descriptor;
    }

    const foo = new Foo();
    expect(foo.foo).toBe('foo');
});

test('修饰静态成员', () => {
    class Foo {
        @Bar
        static foo = 'foo'
    }
    function Bar(target, name, descriptor) {
        expect(typeof target).toBe('function');
        expect(target.name).toBe('Foo');
        expect(name).toBe('foo');
        expect(typeof descriptor).toBe('object');
    }
});

test('修饰类的属性', () => {
    class Foo {
        @Bar
        foo;
    }

    function Bar(target, name, descriptor) {
        expect(target).ok;
        expect(name).toBe('foo');

        descriptor.enumerable = true;
        descriptor.writable = true;
        descriptor.configurable = true;

        return descriptor;
    }

    const foo = new Foo();
    expect(Object.getOwnPropertyDescriptor(foo, 'foo')).toEqual({
            value: undefined,
            writable: true,
            configurable: true,
            enumerable: true,
        });
});

test('修饰器的执行顺序', () => {
    const list = [];

    function Bar(order) {
        list.push(`enter Bar${order}`);
        return (target, property, descriptor) => {
            list.push(`executed Bar${order}`)
            return descriptor;
        };
    }

    class Foo {
        @Bar(1)
        @Bar(2)
        foo() {
        }
    }

    expect(list).toEqual(['enter Bar1', 'enter Bar2', 'executed Bar2', 'executed Bar1']);
});

