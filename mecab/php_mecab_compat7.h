/*
 * macros for compatibility
 */
#ifndef PHP_MECAB_COMPAT_H
#define PHP_MECAB_COMPAT_H

#define MSVC_VA_EXPAND(args) args

#define PHP_MECAB_INTERNAL_RSRC_FROM_PARAMETER() { \
	if (ZEND_NUM_ARGS() != 0) { \
		WRONG_PARAM_COUNT; \
	} else { \
		const php_mecab_object *intern = php_mecab_object_fetch_object(Z_OBJ_P(getThis())); \
		xmecab = intern->ptr; \
	} \
}

#define PHP_MECAB_RSRC_FROM_PARAMETER() \
	PHP_MECAB_INTERNAL_RSRC_FROM_PARAMETER() \
	mecab = xmecab->ptr; \

#define PHP_MECAB_INTERNAL_RSRC_FROM_PARAMETER2(name) { \
	if (ZEND_NUM_ARGS() != 0) { \
		WRONG_PARAM_COUNT; \
	} else { \
		const php_mecab_##name##_object *intern = php_mecab_##name##_object_fetch_object(Z_OBJ_P(getThis())); \
		x##name = intern->ptr; \
	} \
}

#define PHP_MECAB_RSRC_FROM_PARAMETER2(name) \
	PHP_MECAB_INTERNAL_RSRC_FROM_PARAMETER2(name) \
	name = x##name->ptr;

#define PHP_MECAB_PARSE_PARAMETERS(fmt, ...) { \
	if (zend_parse_parameters(ZEND_NUM_ARGS(), fmt, __VA_ARGS__) == FAILURE) { \
		return; \
	} else { \
		const php_mecab_object *intern = php_mecab_object_fetch_object(Z_OBJ_P(getThis())); \
		xmecab = intern->ptr; \
	} \
	mecab = xmecab->ptr; \
}

#define PHP_MECAB_PARSE_PARAMETERS2(name, fmt, ...) { \
	if (zend_parse_parameters(ZEND_NUM_ARGS(), fmt, __VA_ARGS__) == FAILURE) { \
		return; \
	} else { \
		const php_mecab_##name##_object *intern = php_mecab_##name##_object_fetch_object(Z_OBJ_P(getThis())); \
		x##name = intern->ptr; \
	} \
}

#define PHP_MECAB_RETURN_PROPERTY(name, type, ...) { \
	if (ZEND_NUM_ARGS() != 0) { \
		WRONG_PARAM_COUNT; \
	} else { \
		const php_mecab_##name##_object *intern = php_mecab_##name##_object_fetch_object(Z_OBJ_P(getThis())); \
		const php_mecab_##name *x##name = intern->ptr; \
		const mecab_##name##_t *name = x##name->ptr; \
		MSVC_VA_EXPAND(RETURN_##type(__VA_ARGS__)); \
	} \
}

#define PHP_MECAB_FROM_PARAMETER() PHP_MECAB_RSRC_FROM_PARAMETER()
#define PHP_MECAB_NODE_FROM_PARAMETER() PHP_MECAB_RSRC_FROM_PARAMETER2(node)
#define PHP_MECAB_PATH_FROM_PARAMETER() PHP_MECAB_RSRC_FROM_PARAMETER2(path)

#define PHP_MECAB_INTERNAL_FROM_PARAMETER() PHP_MECAB_INTERNAL_RSRC_FROM_PARAMETER()
#define PHP_MECAB_NODE_INTERNAL_FROM_PARAMETER() PHP_MECAB_INTERNAL_RSRC_FROM_PARAMETER2(node)
#define PHP_MECAB_PATH_INTERNAL_FROM_PARAMETER() PHP_MECAB_INTERNAL_RSRC_FROM_PARAMETER2(path)

#define PHP_MECAB_NODE_PARSE_PARAMETERS(fmt, ...) PHP_MECAB_PARSE_PARAMETERS2(node, fmt, __VA_ARGS__)
#define PHP_MECAB_PATH_PARSE_PARAMETERS(fmt, ...) PHP_MECAB_PARSE_PARAMETERS2(path, fmt, __VA_ARGS__)

#define PHP_MECAB_NODE_RETURN_PROPERTY(type, ...) PHP_MECAB_RETURN_PROPERTY(node, type, __VA_ARGS__)
#define PHP_MECAB_PATH_RETURN_PROPERTY(type, ...) PHP_MECAB_RETURN_PROPERTY(path, type, __VA_ARGS__)

#define PHP_MECAB_REGISTER_NS_CONSTANT(name) \
	REGISTER_NS_LONG_CONSTANT("MeCab", #name, MECAB_##name, CONST_PERSISTENT | CONST_CS)

/* PHP < 8.1 */
#ifndef ZEND_BEGIN_ARG_WITH_TENTATIVE_RETURN_TYPE_INFO_EX
#define ZEND_BEGIN_ARG_WITH_TENTATIVE_RETURN_TYPE_INFO_EX(name, return_ref, req_num_args, type, allow_null) \
	ZEND_BEGIN_ARG_INFO_EX(name, 0, return_ref, req_num_args)

#define ZEND_BEGIN_ARG_WITH_TENTATIVE_RETURN_OBJ_INFO_EX(name, return_ref, req_num_args, class_name, allow_null) \
	ZEND_BEGIN_ARG_INFO_EX(name, ZEND_SEND_BY_VAL, return_ref, req_num_args)
#endif

#endif /* PHP_MECAB_COMPAT_H */
