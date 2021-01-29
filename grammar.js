module.exports = grammar({
  name: 'markdown',
  extras: $ => [ /\s+/, ],
  rules: {
    document: $ => seq(repeat($._any)),
    _any: $ => choice($.paragraph),
    text: (_) => /[\w\s]+/,
    bold: $ => prec(2, choice(
      seq("**", $.text, "**"),
      seq("__", $.text, "__"),
    )),
    paragraph: $ => choice(
      $.bold,
      // $.text
    )
  }
});

// text: $ => token(prec.right($._txt)),
// text: $ => token(prec.right(/[^<>]+/)),

