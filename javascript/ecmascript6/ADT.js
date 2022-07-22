



test('Map,Set都使用===判等，但是NaN等于NaN', () => {
    let set = new Set([0, '0']);
    expect(set.size).toBe(2);
    set = new Set([NaN, NaN]);
    expect(set.size).toBe(1);

    let map = new Map();
    map.set(0, '0');
    map.set('0', '0');
    expect(map.size).toBe(2);
    map.clear();
    map.set(NaN, '1');
    map.set(NaN, '2');
    expect(map.size).toBe(1);
});

//Set
// instance method
// add(value)：添加某个值，返回Set结构本身。
// delete(value)：删除某个值，返回一个布尔值，表示删除是否成功。
// has(value)：返回一个布尔值，表示该值是否为Set的成员。
// clear()：清除所有成员，没有返回值。

// keys()：返回键名的遍历器
// values()：返回键值的遍历器
// entries()：返回键值对的遍历器
// forEach()：使用回调函数遍历每个成员

test('Set没有重复值', () => {
    const set = new Set([1, 1, 2]);
    expect(set.size).toBe(2);
});

test('Set构造函数可以接受任意可迭代对象作为参数', () => {
    const obj = {
        *[Symbol.iterator]() {
            yield 'foo';
            yield 'bar';
            yield 'baz';
        }
    };
    const set = new Set(obj);
    expect(set.size).toBe(3);
});

//WeakSet
// add(value)：添加某个值，返回Set结构本身。
// delete(value)：删除某个值，返回一个布尔值，表示删除是否成功。
// has(value)：返回一个布尔值，表示该值是否为Set的成员。
test('WeakSet的成员只能是引用类型', () => {
    const ws = new WeakSet();
    expect(() => ws.add(1)).toThrowError('Invalid value used in weak set');
    const obj = {};
    const arr = [];
    ws.add(obj);
    ws.add(arr);
    expect(ws.has(obj)).toBe(true);
    expect(ws.has(arr)).toBe(true);
});

//Map
test('Map也可以接受一个数组作为参数。该数组的成员是一个个表示键值对的数组', () => {
    const map = new Map([
        ['k1', 'v1'],
        ['k2', 'v2']
    ]);
    expect(map.size).toBe(2);
    expect(map.has('k1')).toBe(true);
    expect(map.has('k2')).toBe(true);
    expect(map.get('k1')).toBe('v1');
    expect(map.get('k2')).toBe('v2');
});

test('读取不存在的值返回undefined', () => {
    const map = new Map();
    expect(map.get('whatever') === undefined).toBe(true);
});

test('Map需要搭配数组方法来实现map与filter', () => {
    expect(Map.prototype.map).toBeFalsy();
    expect(Map.prototype.filter).toBeFalsy();
    const map1 = new Map([[1, 1], [2, 2], [3, 3]]);
    const map2 = new Map([...map1].filter(([k, v]) => k < 3));
    expect(map2.size).toBe(2);
    const map3 = new Map([...map1].map(([k, v]) => [k * 2, v * 2]));
    expect([...map3]).toEqual([[2, 2], [4, 4], [6, 6]]);
});

test('Map.prototype.forEach', () => {
    const map = new Map([[1, 2], [2, 3], [3, 4]]);
    const obj = {};
    map.forEach(function(v,k,m){
        expect(m).not.toEqual(map); //todo:这里两个map为什么不同
        expect(this).toBe(obj);
        expect(v).toBe(k+1);
    }, obj);
});
