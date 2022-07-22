

const utf16str = '\uD83D\uDC2A';

test('es7现在已经支持反向(lookbehind)查找', () => {
    const pattern1 = /(?<=a)b/;
    const pattern2 = /(?<!a)b/;

    expect(pattern1.test('ab')).toBe(true);
    expect(pattern1.test('bb')).toBe(false);

    expect(pattern2.test('ab')).toBe(false);
    expect(pattern2.test('bb')).toBe(true);
});

// u flag
test('u修饰符，用于处理四字节的Unicode字符', () => {
    expect(/^\uD83D/.test(utf16str)).toBe(true);
    expect(/^\uD83D/u.test(utf16str)).toBe(false);
});

test('如果没有u修饰符, 正则元字符无法匹配4字节字符', () => {
    expect(/^.$/.test(utf16str)).toBe(false);
    expect(/^.$/u.test(utf16str)).toBe(true);
});

test('使用es6新增的unicode字符表示方法创建正则0表达式，必须加上u修饰符', () => {
    expect(/\u{61}/.test('a')).toBe(false);//匹配６１个连续的u
    expect(/\u{61}/u.test('a')).toBe(true);
});

test('如果不使用u修饰符,正则表达式量词无法正确匹配４字节字符', () => {
    const str = '𠮷'; //  \u{20BB7}即\uD842\uDFB7
    expect(/𠮷{2}/.test('𠮷𠮷')).toBe(false);
    expect(/𠮷{2}/u.test('𠮷𠮷')).toBe(true);
});

// y flag
test('y修饰符与g修饰符类似，但是y修饰符要求每次匹配都从上次匹配的下一个位置开始', () => {
    const str = 'foo_bar';
    const r1 = /[^_]+/g;
    const r2 = /[^_]+/y;
    expect(r1.exec(str)[0]).toBe('foo');
    expect(r2.exec(str)[0]).toBe('foo');

    expect(r1.exec(str)[0]).toBe('bar');
    expect(r2.exec(str)).toBeFalsy();
});

test('可以认为y修饰符在每次匹配前，为正则表达式添加^锚', () => {
    expect(/b/.test('aba')).toBe(true);
    expect(/b/y.test('aba')).toBe(false);
});

test('如果只有一个y修饰符,match方法只返回第一个匹配，只有与g一起使用才返回所有匹配', () => {
    expect('a1a2a3'.match(/a\d/y).length).toBe(1);
    expect('a1a2a3'.match(/a\d/gy).length).toBe(3);
});

//flag
test('使用source返回文本，使用flags放回所有修饰符', () => {
    const r = /a/gimyu;
    expect(r.source).toBe('a');
    expect(Array.from(r.flags).sort()).toEqual(Array.from('gimyu').sort());
});

test('使用sticky与unicode访问器属性获取正则表达式是否设定了y,u修饰符', () => {
    const r = /a/yu;
    expect(r.sticky).toBe(true);
    expect(r.unicode).toBe(true);
});
