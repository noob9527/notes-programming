// https://leanpub.com/understandinges6/read/#leanpub-auto-proxies-and-the-reflection-api



test('basic usage', () => {
    const target = {};
    const proxy = new Proxy(target, {});
    proxy.name = 'proxy';
    expect(target.name).toBe('proxy')
    target.name = "target";
    expect(proxy.name).toBe('target')
});

test('proxy set behavior', () => {
    // ex: property validation
    const counter = { count: 0 };
    const proxy = new Proxy(counter, {
        set(target, key, value, receiver) {
            expect(target).toBe(counter);
            if(key === 'count' && isNaN(value)) throw new Error('should be number');
            return Reflect.set(target, key, value, receiver);
        }
    });

    proxy.whatever = 'whatever';
    expect(counter.whatever).toBe('whatever');

    proxy.count = 1
    expect(counter.count).toBe(1);

    // manipulate proxy
    expect(() => proxy.count = 'foo').toThrowError('should be number');

    // manipulate origin object
    counter.count = 'foo'
    expect(counter.count).toBe('foo');
});

test('proxy get behavior', () => {
    // ex: object shape validation
    const proxy = new Proxy({}, {
        get(target, key, receiver) {
            if(!(key in receiver))
                throw new Error(`property ${key} does not exist`)
            return Reflect.get(target, key, receiver);
        }
    });
    proxy.foo = 'foo'
    expect(proxy.foo).toBe('foo');
    expect(() => proxy.bar).toThrowError('property bar does not exist')
});

test('proxy has behavior', () => {
    // ex: hide property
    const proxy = new Proxy({ 
        foo: 'foo',
        bar: 'bar'
    }, {
        has(target, key) {
            return key === 'bar' ? false : Reflect.has(target, key);
        }
    });
    expect('foo' in proxy).toBe(true);
    expect('bar' in proxy).toBe(false);
});

test('proxy apply behavior', () => {
    const sumProxy = new Proxy(
        (...args) => args.reduce((acc, curr) => acc + curr, 0),
        {
            apply(target, thisArg, args) {
                args.forEach(arg => {
                    if(typeof arg !== 'number')
                        throw new Error('argument must be number');
                });
                return Reflect.apply(target, thisArg, args);
            }
        }
    );
    expect(sumProxy(1, 2)).toBe(3);
    expect(() => sumProxy(1, '2')).toThrowError('argument must be number');
});

test('proxy construct behavior', () => {
    function Foo() {}
    const NonInstantiable = new Proxy(Foo, {
        construct(target, args) {
            throw new Error('can not be instantiate');
        }
    });

    const foo = new Foo();
    expect(foo instanceof Foo).toBe(true);
    expect(() => new NonInstantiable()).toThrowError('can not be instantiate');
    // test new.target in function implementation is preferable,
    // But sometimes you aren’t in control of the function
    // whose behavior needs to be modified. In that case
    // using a proxy makes sense.
    function Bar() {
        if(new.target) {
            throw new Error('can not be instantiate');
        }
    }
    expect(() => new Bar()).toThrowError('can not be instantiate');
});

test('revocable', () => {
    // proxy - the proxy object that can be revoked
    // revoke - the function to call to revoke the proxy
    const { proxy, revoke } = Proxy.revocable({ foo: 'foo' }, {});
    expect(proxy.foo).toBe('foo');
    revoke();
    expect(() => proxy.foo).toThrow();
});

// Only the get, set, and has proxy traps will ever be
// called on a proxy when it’s used as a prototype
test('using a proxy as a prototype', () => {
    let target = {};
    let thing = Object.create(new Proxy(target, {
        get(target, key, receiver) {
            // whenever subClass access properties which
            // they dosn't own, throw an error
            throw new Error(`${key} does not exist`);
        }
    }));

    thing.name = 'thing';
    expect(thing.name).toBe('thing');
    expect(() => thing.unknown).toThrowError('unknown does not exist')
});
