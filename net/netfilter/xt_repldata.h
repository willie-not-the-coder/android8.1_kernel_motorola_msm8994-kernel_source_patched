/*
 * Today's hack: quantum tunneling in structs
 *
 * 'entries' and 'term' are never anywhere referenced by word in code. In fact,
 * they serve as the hanging-off data accessed through repl.data[].
 */

#define xt_alloc_initial_table(type, typ2) ({ \
	unsigned int hook_mask = info->valid_hooks; \
	unsigned int nhooks = hweight32(hook_mask); \
	unsigned int bytes = 0, hooknum = 0, i = 0; \
	struct type##_replace *repl; \
	struct type##_standard *entries; \
	struct type##_error *term; \
	/* GCC 4.9 accepted a variable-length member in this temporary \
	 * statement-expression struct. Keep the exact byte layout without \
	 * relying on a VLA member, so Clang can compile the same logic. */ \
	repl = kzalloc(sizeof(*repl) + \
		nhooks * sizeof(*entries) + sizeof(*term), GFP_KERNEL); \
	if (repl == NULL) \
		return NULL; \
	entries = (struct type##_standard *)((char *)repl + sizeof(*repl)); \
	term = (struct type##_error *)((char *)entries + \
		nhooks * sizeof(*entries)); \
	strncpy(repl->name, info->name, sizeof(repl->name)); \
	*term = (struct type##_error)typ2##_ERROR_INIT;  \
	repl->valid_hooks = hook_mask; \
	repl->num_entries = nhooks + 1; \
	repl->size = nhooks * sizeof(struct type##_standard) + \
	             sizeof(struct type##_error); \
	for (; hook_mask != 0; hook_mask >>= 1, ++hooknum) { \
		if (!(hook_mask & 1)) \
			continue; \
		repl->hook_entry[hooknum] = bytes; \
		repl->underflow[hooknum]  = bytes; \
		entries[i++] = (struct type##_standard) \
			typ2##_STANDARD_INIT(NF_ACCEPT); \
		bytes += sizeof(struct type##_standard); \
	} \
	repl; \
})
