

Reflect.defineProperty(Object.prototype, 'log', {
    get: function () {
        console.log(this);
    }
});

test('promise的执行顺序', done => {
    let count = 0;
    const promise = new Promise(function (resolve, reject) {
        expect(count++).toBe(0); //最先执行
        resolve();
    });

    promise.then(() => {
        expect(count++).toBe(2) //最后执行
        done();
    });

    expect(count++).toBe(1);
});

//Promise.resolve, Promise.reject
test('使用Promise静态方法将值包装成promise', async () => {
    const p1 = Promise.resolve('foo');
    const p2 = Promise.reject('bar');
    await p1.then(v => expect(v).toBe('foo'));
    await p2.catch(v => expect(v).toBe('bar'));
});

test('不使用任何参数调用Promise.resolve, Promise.reject，传给回调函数的参数为undefined', async () => {
    const p1 = Promise.resolve();
    const p2 = Promise.reject();
    await p1.then(v=>expect(v).toBeFalsy());
    await p2.catch(v=>expect(v).toBeFalsy());
});

test('Promise.resolve对promise对象返回其本身，对有then方法的对象会执行其then方法，并等待其resolve', async () => {
    const thenable = {
        then(resolve,reject){
            resolve('foo');
        }
    }
    const p1 = Promise.resolve();
    expect(Promise.resolve(p1)).toBe(p1);

    const p2 = Promise.resolve(thenable);
    await p2.then(v=>expect(v).toBe('foo'));
});

test('如果promise已经resolve，依然可以调用then方法获得返回值', async () => {
    const p1 = Promise.resolve('foo');
    const p2 = Promise.reject('bar');
    await p1.then(v => expect(v).toBe('foo'));
    await p1.then(v => expect(v).toBe('foo'));
    await p2.catch(v => expect(v).toBe('bar'));
    await p2.catch(v => expect(v).toBe('bar'));
});

//Promise.all与Promise.race
test('Promise.all与Promise.race会自动调用Promise.resolve包装数组中不是promise的值', async () => {
    const arr = [0, Promise.resolve(1)];
    await Promise.all(arr).then(v => expect(v).toEqual([0, 1]));
    await Promise.race(arr).then(v => expect(v).toBe(0));
});

