Reflect.defineProperty(Object.prototype, 'log', {
    get: function () {
        console.log(this);
    }
});

test('class关键字只是语法糖，其数据类型是函数', () => {
    class Person {
    }

    expect(typeof Person).toBe('function');
    expect(Person).toBe(Person.prototype.constructor);
});

test('类的方法都定义在函数的prototype中', () => {
    class Foo {
        foo() {
            return 'foo';
        }
    }

    const foo = new Foo();
    expect(foo.foo()).toBe('foo');
    expect(Foo.prototype.foo()).toBe('foo');
    expect(Reflect.deleteProperty(Foo.prototype, 'foo')).toBe(true);
    Foo.prototype.bar = () => 'bar';
    expect(foo.foo).toBeFalsy();
    expect(foo.bar()).toBe('bar');
});

test('类里面定义的方法都是不可枚举的', function () {
    class Foo {
        foo() {
        }
    }

    Foo.prototype.bar = () => 'bar'; //如果使用这种方法为'类'添加方法，该方法是可枚举属性
    expect(Reflect.getOwnPropertyDescriptor(Foo.prototype, 'foo')
        .enumerable).toBe(false);
    expect(Reflect.getOwnPropertyDescriptor(Foo.prototype, 'bar')
        .enumerable).toBe(true);
});

test('类的数据类型虽然是函数，但它必须使用new关键字调用', () => {
    class Foo {
    }

    expect(typeof Foo).toBe('function');
    expect(() => Foo()).toThrowError("Class constructor Foo cannot be invoked without 'new'");
});

// see also: es5
// search the following content
// 如果构造函数使用return语句显式返回一个对象，则调用表达式的结果为该对象，而新创建的对象会被抛弃
// 如果构造函数使用了return语句，没有指定返回值，或者返回的是primitive类型的值, 则抛弃该返回值，使用新对象作为调用表达式的结果
describe('构造函数显式返回值', () => {
    test('basic case', () => {
        const obj = {};

        class Sample {
            constructor() {
                return obj;
            }
        }

        expect(new Sample()).toBe(obj);
    });
    test('构造函数显式返回 primitive 值, 则使用生成的新对象作为 new 表达式的结果', () => {
        class Parent {
            constructor() {
                return 1;
            }
        }

        class Child extends Parent {
        }

        const parent = new Parent();
        expect(parent).not.toBe(1);
        expect(parent).toBeInstanceOf(Object);
        const child = new Child();
        expect(child).not.toBe(1);
        expect(child).toBeInstanceOf(Object);
    });
    test('父类构造函数显式返回值', () => {
        const obj = {};

        class Parent {
            constructor() {
                return obj;
            }
        }

        class Child extends Parent {
        }

        expect(new Parent()).toBe(obj);
        expect(new Child()).toBe(obj);
    });
    test('父类函数显式返回值', () => {
        const obj = {};

        function Parent() {
            return obj;
        }

        class Child extends Parent {
        }

        expect(new Parent()).toBe(obj);
        expect(new Child()).toBe(obj);
    });
    test('如果构造函数显示返回值，instanceof 可能会让人迷惑', () => {
        class Foo {
        }

        class Bar {
            constructor() {
                return new Foo();
            }
        }

        expect(new Bar() instanceof Bar).toBe(false);
        expect(new Bar() instanceof Foo).toBe(true);
    });
})

test('类的定义不存在变量提升', () => {
    expect(Foo).toBeDefined();
    expect(() => Bar).toThrow()

    function Foo() {
    }

    class Bar {
    }
});

test('与函数一样，可以使用表达式形式定义类', () => {
    const Foo = class {
    };
    expect(new Foo() instanceof Foo).toBe(true);
});

test('使用表达式时也可以为类指定名称，但该名称只能在类的内部使用', () => {
    const Foo = class Bar {
        getClassName() {
            return Bar.name;
        }
    }
    expect(() => Bar).toThrowError('Bar is not defined');
    expect((new Foo()).getClassName()).toBe('Bar');
});

test('类与函数一样带有name属性，且该属性优先返回紧跟在class关键字后的类名', () => {
    const Foo1 = class {
    }
    expect(Foo1.name).toBe('Foo1');
    const Foo2 = class Bar {
    }
    expect(Foo2.name).toBe('Bar');
});

test('使用表达式定义类，可以写出立即执行的类', () => {
    const foo = new class {
        constructor(name) {
            this.name = name;
        }
    }('foo');
    expect(foo.name).toBe('foo');
});

test('类的方法内部的this指向该类的实例，因此如果用到this, 则该方法不能作为函数调用', () => {
    class Foo {
        foo() {
            return this.bar();
        }

        bar() {
            return 'bar';
        }
    }

    let fn = (new Foo()).foo;
    expect(fn).toThrowError("undefined");

    //一种解决方案是使用bind绑定this
    class Foo1 {
        constructor() {
            this.foo = this.foo.bind(this);
        }

        foo() {
            return this.bar();
        }

        bar() {
            return 'bar';
        }
    }

    fn = (new Foo1()).foo;
    expect(fn()).toBe('bar');

    //另一种方法是使用箭头函数
    class Foo2 {
        constructor() {
            this.foo = () => this.bar();
        }

        bar() {
            return 'bar';
        }
    }

    fn = (new Foo2()).foo;
    expect(fn()).toBe('bar');
});

//class extend
test('使用extend关键字实现继承', () => {
    class Parent {
        constructor(name) {
            this.name = name;
        }

        sayName() {
            return this.name;
        }
    }

    //es5继承
    const Child1 = function (name) {
        this.name = name;
        // Parent.apply(this, arguments);
    }
    //Child1的实例继承Parent的实例
    Child1.prototype.__proto__ = Parent.prototype;
    Child1.__proto__ = Parent;

    const child1 = new Child1('foo');
    expect(child1.sayName()).toBe('foo');
    expect(child1 instanceof Parent).toBe(true);

    //es6
    class Child2 extends Parent {
    }

    const child2 = new Child2('foo');
    expect(child2.sayName()).toBe('foo');
    expect(child2 instanceof Parent).toBe(true);
});

test('类继承的实现', () => {
    class Parent {
    }

    class Child extends Parent {
    }

    // 对比 es5 实现继承的方法
    // Child1.prototype.__proto__ = Parent.prototype;
    // Child1.__proto__ = Parent;
    expect(Reflect.getPrototypeOf(Child.prototype)).toBe(Parent.prototype);
    expect(Reflect.getPrototypeOf(Child)).toBe(Parent);
});

test('子类如果有自己的构造函数，则必须在该函数中调用父类构造函数', () => {
    class Parent {
    }

    class Child1 extends Parent {
    }

    //如果子类没有定义constructor ,会有如下的默认构造函
    // constructor(...args) {
    //     super(...args);
    // }
    class Child2 extends Parent {
        constructor() {
        }
    }

    class Child3 extends Parent {
        constructor() {
            super();
        }
    }

    expect(new Child1()).toBeDefined();
    expect(() => new Child2()).toThrow();
    expect(new Child3()).toBeDefined();
});

test('子类构造函数只有调用父类构造函数后，才能获取this引用', () => {
    class Parent {
    }

    class Child extends Parent {
        constructor() {
            expect(this).toBeFalsy();
            super();
            expect(this).toBeDefined();
        }
    }
});

//super关键字
// Note: super is a keyword and these are special syntactic constructs.
// super is not a variable that points to the prototype object.
// Attempting to read super itself is a SyntaxError.
// https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Operators/super#description
test('子类中的super关键字指向父类的原型对象', () => {
    class Parent {
    }

    class Child extends Parent {
        constructor() {
            super();
            // console.log(super); // SyntaxError: 'super' keyword unexpected here
            // expect(super).toBe(Parent.prototype); // this used to work, but doesn't work anymore
            expect(super.constructor).toEqual(Parent);
        }
    }

    new Child();
});

test('使用super调用父类方法时，this指向子类的实例', () => {
    class Parent {
        name() {
            return this.name;
        }
    }

    class Child extends Parent {
        constructor() {
            super();
            this.name = 'child';
        }

        name() {
            expect(super.name()).toBe('child');
        }
    }
});

test('在子类中对super属性赋值，实际上等价于对this赋值', () => {
    class Parent {
    }

    class Child extends Parent {
        constructor() {
            super();
            this.x = 1;
            super.x = 2;
            expect(super.x).toBeFalsy()
            expect(this.x).toBe(2);
        }
    }

    new Child();
});

test('es6 class能够正确继承原生的构造函数', () => {
    function ES5Array() {
        Array.apply(this, arguments);
    }

    ES5Array.prototype.__proto__ = Array.prototype;
    //es5得到的行为与Array不一致
    let arr = new ES5Array();
    arr[0] = 1;
    expect(arr.length).toBe(0);

    //es6正常
    class ES6Array extends Array {
    }

    arr = new ES6Array();
    arr[0] = 1;
    expect(arr.length).toBe(1);
});

//static
test('使用static关键字定义静态方法，静态方法可以被子类继承', () => {
    class Foo {
        static foo() {
            return 'foo';
        }
    }

    class Bar extends Foo {
    }

    expect(Foo.foo()).toBe('foo');
    expect((new Foo).foo).toBeFalsy();
    expect(Bar.foo()).toBe('foo');
});

test('使用static关键字定义静态属性,静态属性同样可以被子类继承', () => {
    class Foo {
        static foo = 'foo';
    }

    class Bar extends Foo {
    }

    expect(Foo.foo).toBe('foo');
    expect((new Foo).foo).toBeFalsy();
    expect(Bar.foo).toBe('foo');
});

test('可以通过super关键字调用父类的静态方法', () => {
    class Foo {
        static foo() {
            return 'foo';
        }
    }

    class Bar extends Foo {
        static bar() {
            return super.foo();
        }
    }

    expect(Bar.bar()).toBe('foo');
});

test('实例属性在类的内部使用等式定义，或在类的方法中使用this定义', () => {
    class Foo {
        prop1 = 1;
        static prop2 = 2;

        constructor() {
            this.prop3 = 3;
        }
    }

    Foo.prop4 = 4;
    const foo = new Foo();
    expect(foo.prop1).toBe(1);
    expect(Foo.prop2).toBe(2);
    expect(foo.prop3).toBe(3);
    expect(Foo.prop4).toBe(4);
});

test('属性赋值可以使用表达式', () => {
    const prop1 = 'prop1';
    const prop2 = Symbol('prop2');
    const prop3 = Symbol('prop3');

    class Foo {
        [prop1] = 1;
        [prop2] = 2;
        static [prop3] = 3;
    }

    const foo = new Foo();
    expect(foo[prop1]).toBe(1);
    expect(foo[prop2]).toBe(2);
    expect(Foo[prop3]).toBe(3);
});

//new.target
test('使用new.target访问new命令作用的构造函数', () => {
    function Fn1() {
        expect(new.target).toBe(Fn1);
    }

    function Fn2() {
        expect(new.target).toBeFalsy();
    }

    new Fn1();
    Fn2();
});

test('在class中使用new.target访问当前类，如果一个类继承另一个类，则new.target返回子类', () => {
    class Parent {
        constructor() {
            expect(new.target).toBe(Child);
        }
    }

    class Child extends Parent {
        constructor() {
            super();
            expect(new.target).toBe(Child);
        }
    }

    new Child();
});
