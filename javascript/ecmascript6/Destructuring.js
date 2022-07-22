


test('基础用法', () => {
    const [a, b] = [1, 2];
    expect(a).toBe(1);
    expect(b).toBe(2);
});

test('使用逗号跳过元素', () => {
    const [, , third] = ['foo', 'bar', 'baz'];
    expect(third).toBe('baz');
});

test('使用...获取不定项参数', () => {
    const [foo, ...bar] = [1, 2, 3, 4];
    expect(foo).toBe(1);
    expect(bar).toEqual([2, 3, 4]);
});

test('解构失败，则变量等于undefined', () => {
    const [a] = [];
    const [b, c] = [1];
    expect(a === undefined).toBe(true);
    expect(c === undefined).toBe(true);
});

test('解构赋值可以使用默认值', () => {
    let [foo = 'bar'] = [];
    expect(foo).toBe('bar');
    [foo = 'bar'] = ['abc'];
    expect(foo).toBe('abc');
    [foo = 'bar'] = [undefined]; //只有在对应位置严格等于undefined时，默认值才会生效
    expect(foo).toBe('bar');
    [foo = 'bar'] = [null];
    expect(foo === null).toBe(true);
});

test('解构赋值可以作用于对象', () => {
    let {foo, bar} = { foo: 'a', bar: 'b' };
    expect(foo).toBe('a');
    expect(bar).toBe('b');
});

test('如果变量名在对象中不存在，则需要指明变量应该对应于对象的哪个属性', () => {
    let {foo: aaa, bbb} = { foo: 'a', bar: 'b' };
    expect(aaa).toBe('a');
    expect(bbb).toBeFalsy();
});

test('解构赋值复杂对象', () => {
    const obj = {
        bar:'aaa',
        baz:{
            bbb:'bbb',
            ccc:'ccc',
        },
        qux:['ddd', 'eee'],
    }

    let {
        foo='foo',
        bar:aaa,
        baz:{
            bbb,
            ccc,
        },
        qux:[ddd,eee],
    } = obj;

    expect(typeof bar).toBe('undefined');
    expect(typeof baz).toBe('undefined');
    expect(typeof qux).toBe('undefined');

    expect({foo, aaa, bbb, ccc}).toEqual({
        foo:'foo',
        aaa:'aaa',
        bbb:'bbb',
        ccc:'ccc',
    });
});

test('解构赋值等号右侧如果是原始数据类型，则会先被转换成对应的包装类型', () => {
    let [a, b] = 'foo';
    expect(a).toBe('f');
    expect(b).toBe('o');
    let {toString} = 123;
    expect(toString).toBe(Number.prototype.toString);
    ({ toString } = true);
    expect(toString).toBe(Boolean.prototype.toString);
});

test('函数参数解构1', () => {
    const arr = [[1, 2], [3, 4]].map(([a, b]) => a + b); //注意这里的b不是index，而是参数数组的第二个元素
    expect(arr).toEqual([3, 7]);
});

test('函数参数解构2', () => {
    const fn = ({
        foo,
        bar='bar',
        baz:aaa,
        qux:{
            bbb,
            ccc,
        }
    }) => {
        return {
            foo,
            bar,
            aaa,
            bbb,
            ccc,
        };
    }

    const result = fn({
        foo:'foo',
        baz:'baz',
        qux:{
            bbb:'bbb',
            ccc:'ccc',
        },
    });

    expect(result).toEqual({
        foo:'foo',
        bar:'bar',
        aaa:'baz',
        bbb:'bbb',
        ccc:'ccc',
    });
});
