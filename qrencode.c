/*
 * php-qrencode
 *
 * ORIGINAL AUTHOR, LICENSE AND COPYRIGHT OWNER NOT KNOWN
 * CODE ORIGINALLY FROM http://hirokawa.netflowers.jp/entry/4900/
 * BUT NO LONGER AVAILABLE.
 *
 * THE FOLLOWING COPYRIGHT NOTICE IS ENTIRELY DEPENDENT ON
 * THE WISHES OF THE ORIGINAL AUTHOR.
 *
 * Copyright (c) 2012 Colin Viebrock <colin@viebrock.ca>
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject
 * to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

#include "php_qrencode.h"

#if HAVE_QRENCODE

/* {{{ qrencode_functions[] */
#if (PHP_MAJOR_VERSION == 5 && PHP_MINOR_VERSION < 4) || (PHP_MAJOR_VERSION < 5)
function_entry qrencode_functions[] = {
#else
static zend_function_entry qrencode_functions[] = {
#endif
	PHP_FE(qrencode, NULL)
	{ NULL, NULL, NULL }
};
/* }}} */


/* {{{ qrencode_module_entry
 */
zend_module_entry qrencode_module_entry = {
	STANDARD_MODULE_HEADER,
	"qrencode",
	qrencode_functions,
	PHP_MINIT(qrencode),     /* Replace with NULL if there is nothing to do at php startup   */
	PHP_MSHUTDOWN(qrencode), /* Replace with NULL if there is nothing to do at php shutdown  */
	PHP_RINIT(qrencode),     /* Replace with NULL if there is nothing to do at request start */
	PHP_RSHUTDOWN(qrencode), /* Replace with NULL if there is nothing to do at request end   */
	PHP_MINFO(qrencode),
	"0.0.2-prestoh",
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_QRENCODE
ZEND_GET_MODULE(qrencode)
#endif


/* {{{ PHP_MINIT_FUNCTION */
PHP_MINIT_FUNCTION(qrencode)
{
	REGISTER_LONG_CONSTANT("QR_MODE_NUM", QR_MODE_NUM, CONST_PERSISTENT | CONST_CS);
	REGISTER_LONG_CONSTANT("QR_MODE_AN", QR_MODE_AN, CONST_PERSISTENT | CONST_CS);
	REGISTER_LONG_CONSTANT("QR_MODE_8", QR_MODE_8, CONST_PERSISTENT | CONST_CS);
	REGISTER_LONG_CONSTANT("QR_MODE_KANJI", QR_MODE_KANJI, CONST_PERSISTENT | CONST_CS);
	REGISTER_LONG_CONSTANT("QR_ECLEVEL_L", QR_ECLEVEL_L, CONST_PERSISTENT | CONST_CS);
	REGISTER_LONG_CONSTANT("QR_ECLEVEL_M", QR_ECLEVEL_M, CONST_PERSISTENT | CONST_CS);
	REGISTER_LONG_CONSTANT("QR_ECLEVEL_Q", QR_ECLEVEL_Q, CONST_PERSISTENT | CONST_CS);
	REGISTER_LONG_CONSTANT("QR_ECLEVEL_H", QR_ECLEVEL_H, CONST_PERSISTENT | CONST_CS);

	/* add your stuff here */

	return SUCCESS;
}
/* }}} */


/* {{{ PHP_MSHUTDOWN_FUNCTION */
PHP_MSHUTDOWN_FUNCTION(qrencode)
{

	/* add your stuff here */

	return SUCCESS;
}
/* }}} */


/* {{{ PHP_RINIT_FUNCTION */
PHP_RINIT_FUNCTION(qrencode)
{
	/* add your stuff here */

	return SUCCESS;
}
/* }}} */


/* {{{ PHP_RSHUTDOWN_FUNCTION */
PHP_RSHUTDOWN_FUNCTION(qrencode)
{
	/* add your stuff here */

	return SUCCESS;
}
/* }}} */


/* {{{ PHP_MINFO_FUNCTION */
PHP_MINFO_FUNCTION(qrencode)
{
	php_info_print_box_start(0);
	php_printf("<p>QRCode Extension</p>\n");
	php_printf("<p>Version 0.0.3</p>\n");
	php_info_print_box_end();
	/* add your stuff here */

}
/* }}} */


/* {{{ proto array qrencode(string text,int version,int level,int mode)
   */
PHP_FUNCTION(qrencode)
{
	const char * text = NULL;
	int text_len = 0;
	long version = 0;
	long level = 0;
	long mode = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "slll", &text, &text_len, &version, &level, &mode) == FAILURE) {
		return;
	}
	array_init(return_value);

	do {
//		QRinput *input;
		QRcode *code;
		unsigned char *p;
		int x,y;

//		input = QRinput_new();
//		QRinput_append(input,mode,text_len,text);
		// as per ttp://hirokawa.netflowers.jp/entry/4900/#comment_51714
		//code = QRcode_encodeInput(input,version,level);
		//code = QRcode_encodeInput(input);

		//code = QRcode_encodeString(text, version, level, mode);

		code = QRcode_encodeString(text, version, level, mode, 1);


		if(code == NULL) {
			RETURN_FALSE;
		}

		array_init(return_value);

		p = code->data;
		for(y=0;y<code->width;y++){

			zval *new_array;
			MAKE_STD_ZVAL(new_array);
			array_init(new_array);

			for(x=0;x<code->width;x++){
				add_next_index_long(new_array, (*p &1)?1:0);
				p++;
			}
			add_next_index_zval(return_value, new_array);
		}

//		QRinput_free(input);
		QRcode_free(code);
	} while (0);
}
/* }}} qrencode */

#endif /* HAVE_QRENCODE */


/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
