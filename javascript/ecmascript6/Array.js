


//Array.from
test('Array.from可以将类数组对象与可遍历的对象转换为数组', () => {
    expect(Array.from('abc')).toEqual(['a', 'b', 'c']);
    expect(Array.from({ length: 2 })).toEqual([undefined, undefined]);
    expect(Array.from(new Set(['a', 'b']))).toEqual(['a', 'b']);
});

test('如果参数是数组，则返回一模一样的新数组，但不包含额外属性', () => {
    const arr = [1, 2, 3];
    arr.foo = 'bar';
    const copy = Array.from(arr);
    expect(copy).not.toBe(arr);
    expect(copy).toEqual([1, 2, 3]);
    expect(copy.foo).toBeFalsy();
});

test('Array.from会使用undefined填充空位', () => {
    expect(Array.from({ length: 2 })).toEqual([undefined, undefined]);
    expect(Array.from([1, , 2])).toEqual([1, undefined, 2]);
});

test('Array.from接收第二个参数，其作用类似于map方法', () => {
    expect(Array.from({ length: 2 }, (e, i) => i)).toEqual([0, 1]);
});

test('由于Array.from方法能够正确处理４字节unicode字符，因此可用于统计字符数', () => {
    expect('𠮷'.length).toBe(2);
    expect(Array.from('𠮷').length).toBe(1);
});

//Array.of
test('Array.of用于将一组值转换为数组', () => {
    expect(Array.of(1, 2, 3)).toEqual([1, 2, 3]);
});

test('Array.of()与Array()的主要区别', () => {
    expect(Array(1)).toEqual([,]);
    expect(Array.of(1)).toEqual([1]);
});

//copyWithin(target, start=0, end=this.length)
test('copyWithin会修改原数组', () => {
    const arr = [1, 2, 3];
    arr.copyWithin(1);
    expect(arr).toEqual([1, 1, 2]);
});

test('copyWithin会拷贝数组空位', () => {
    expect([, 1, 2].copyWithin(1)).toEqual([, , 1]);
});

//find findIndex
test('find与findIndex能够发现NaN', () => {
    expect([NaN].indexOf(NaN)).toBe(-1);
    [NaN].findIndex(e => Object.is(NaN, e));
});

//fill
test('fill使用指定元素填充数组', () => {
    expect([1, 2, 3].fill(0)).toEqual([0, 0, 0]);
});

test('fill的其它参数用于控制填充的起始与结束位置', () => {
    expect([1, 2, 3].fill(0, 1, 2)).toEqual([1, 0, 3]);
});

//entries, keys
test('entries, keys返回遍历器', () => {
    const arr = [5, 6, 7]
    expect(arr.keys().next().value).toBe(0);
    expect(arr.entries().next().value).toEqual([0, 5]);
});

//includes
test('includes的第二个参数指定搜索的起始位置', () => {
    expect([1, 2, 3].includes(1)).toBe(true);
    expect([1, 2, 3].includes(1, 1)).toBe(false);
});

test('includes能够正确查找NaN', () => {
    expect([NaN].indexOf(NaN)).toBe(-1);
    expect([NaN].includes(NaN)).toBe(true);
});

//for of
test('for of不会跳过数组空位', () => {
    const arr = [,];
    let res = [];
    arr.forEach(i => res.push(i));
    expect(res).toEqual([]);
    res = [];
    for (let i of arr) {
        res.push(i);
    }
    expect(res).toEqual([undefined]);
});

test('快速排序的es2015实现', () => {
    function quickSort(arr) {
        if (!arr.length) return [];
        const [pivot, ...rest] = arr;
        return [
            ...quickSort(rest.filter(x => x < pivot)),
            pivot,
            ...quickSort(rest.filter(x => x >= pivot))
        ]
    }
    expect(quickSort([3, 5, 1, 4, 2])).toEqual([1, 2, 3, 4, 5]);
});
