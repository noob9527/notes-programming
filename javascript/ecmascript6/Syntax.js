


//spread operator
test('扩展运算符主要用于将数组转换为参数序列', () => {
    const arr = [];
    arr.push(...[1,2,3]);
    expect(arr).toEqual([1,2,3]);
});

test('扩展运算符可以用来取代concat实现合并数组',() => {
    const arr1 = [1,2,3];
    const arr2 = [4,5,6];
    expect(arr1.concat(arr2)).toEqual([...arr1,...arr2]);
});

test('如果对象实现了Symbol.iterator接口,则可以使用扩展运算符将其“转换”为数组', () => {
    const set = new Set([1, 2, 3]);
    expect([...set]).toEqual([1, 2, 3]);
    const str = 'abc';
    expect([...str]).toEqual(['a', 'b', 'c']);
});

test('扩展运算符可以与解构赋值搭配使用，用于生成数组',() => {
    const arr = [1,2,3];
    const [first,...rest] = arr;
    expect(rest).toEqual([2,3]);
});
