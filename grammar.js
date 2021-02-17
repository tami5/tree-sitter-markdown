module.exports = grammar({
  name: 'markdown',
  extras: $ => [ /\s+/, ],
  conflicts: $ => [
    [$.paragraph, $.paragraph]
  ],
  rules: {
    document: $ => seq(repeat($._any)),
    _any: $ => choice($.paragraph),
    text: (_) => /[\w\s]+/,

    // Styles
    // ----------------------------------
    bold: $ => choice(
      seq("**", $.text, "**"),
      seq("__", $.text, "__")),

    paragraph: $ => choice(
      repeat1($.bold),
      // $.text,
    )
  }
});
// whitespace [\n# $&:\n\t]
// text: $ => token(prec.right($._txt)),
// text: $ => token(prec.right(/[^<>]+/)),

