module.exports = grammar({
  name: 'markdown',
  extras: $ => [
    /\s+/,
  ],
  rules: {
    document: $ => 'hello'
  }
});
