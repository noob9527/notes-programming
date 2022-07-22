


//utf16
test('新增表示unicode字符的方法', () => {
    expect('\u{7a}').toBe('\u007a');
    expect('\u{1F680}').toBe('\uD83D\uDE80');
});

//include,startWith,endsWith
test('includes, startWith, endWith可以使用第二个参数指定搜索的位置', () => {
    expect('whatever'.includes('what')).toBe(true);
    expect('whatever'.includes('what', 1)).toBe(false);
});

test('endsWith使用第二个参数指定搜索的字符数(前n个字符)', () => {
    expect('whatever'.endsWith('at')).toBe(false);
    expect('whatever'.endsWith('at', 4)).toBe(true);
});

//repeat
test('repeat的参数如果是负数或者infinity则会报错', () => {
    expect(() => { return 'foo'.repeat(-1); }).toThrowError('Invalid count value');
});

test('repeat的参数如果是字符串，则会自动转换为数字，如果是小数则会先取整', () => {
    expect('foo'.repeat(-0.5)).toBe('');
    expect('foo'.repeat(1.9)).toBe('foo');
    expect('foo'.repeat('2')).toBe('foofoo');
});

//padStart,padEnd
test('原字符串大于等于最小长度，则返回原字符串', () => {
    expect('foo'.padStart(3, 'bar')).toBe('foo');
});

test('如果补全字符串与原字符串二者长度之和超过指定的最小长度，则截取补全字符串', () => {
    expect('foo'.padStart(4, 'bar')).toBe('bfoo');
});

test('如果补全字符串与原字符串二者长度之和仍不足最小长度，则重复补全字符串', () => {
    expect('foo'.padStart(8, 'bar')).toBe('barbafoo');
});

test('如果省略第二个参数，则默认用空格补全字符串', () => {
    expect(''.padStart(2)).toBe('  ');
});

test('padStart可以用来生成前导０', () => {
    expect('1'.padStart(5, '0')).toBe('00001');
});

//template String
test('使用模板字符串在字符串中嵌入变量', () => {
    const foo = 'foo';
    expect(`hello ${foo}`).toBe('hello foo');
});

test('``中的空格与缩进会保留在结果字符串中', () => {
    expect(`
    foo`.startsWith('\n')).toBe(true);
});

test('模板字符串可以嵌套', () => {
    expect(`foo ${`bar ${'baz'}`}`).toBe('foo bar baz');
});
