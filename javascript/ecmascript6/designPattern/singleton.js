

Reflect.defineProperty(Object.prototype, 'log', {
    get: function () {
        console.log(this);
    }
});

test('singleton', () => {
    class Singleton{
        static instance = null;
        constructor(){
            if(Singleton.instance) return Singleton.instance;
            return Singleton.instance = this;
        }
    }
    const foo = new Singleton();
    const bar = new Singleton();
    expect(foo).toBe(bar);
});
