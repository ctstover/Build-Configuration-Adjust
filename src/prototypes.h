/* GPLv3

    Build Configuration Adjust, a source configuration and Makefile
    generation tool. Copyright © 2011-2014 Stover Enterprises, LLC
    (an Alabama Limited Liability Corporation), All rights reserved.
    See http://bca.stoverenterprises.com for more information.

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/


#ifndef _prototypes_h_
#define _prototypes_h_

#ifndef IN_SINGLE_FILE_DISTRIBUTION
#include "config.h"
#endif

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <sys/wait.h>
#include <errno.h>

#ifdef HAVE_CWD
#include <unistd.h>
#endif

#define NEW_PROJECT_MODE                           2
#define REMOVE_VALUE_MODE                          4
#define SHOW_VALUE_MODE                            5
#define SET_VALUE_MODE                             6
#define ADD_VALUE_MODE                             7
#define PULL_VALUE_MODE                            8
#define CHECK_VALUE_MODE                           9
#define SMART_ADD_VALUE_MODE                       10
#define SMART_PULL_VALUE_MODE                      11
#define STRING_REPLACE_MODE                        15
#define SHORT_HELP_MODE                            19
#define NEW_COMPONENT_MODE                         20
#define CONFIGURE_MODE                             30
#define GENERATE_GMAKEFILE_MODE                    40
#define CONCATENATE_MODE                           50
#define FILE_TO_C_SOURCE_MODE                      51
#define GENERATE_GRAPHVIZ_MODE                     60
#define NEWT_INTERFACE_MODE                        70
#define GTK_INTERFACE_MODE                         72
#define LIST_HOSTS_MODE                            80
#define LIST_PROJECT_TYPES_MODE                    81
#define LIST_PLATFORM_DETIALS_MODE                 82
#define LIST_PROJECT_COMPONENTS_MODE               83
#define LIST_COMPONENT_OUTPUT_NAMES_MODE           84
#define LIST_COMPONENT_BUILD_OUTPUT_NAMES_MODE     85
#define LIST_COMPONENT_INSTALL_OUTPUT_NAMES_MODE   86
#define LIST_COMPONENT_EFFECTIVE_OUTPUT_NAMES_MODE 87
#define SELF_TEST_MODE                             99
#define VERSION_MODE                               100
#define OUTPUT_CONFIGURE_MODE                      110
#define OUTPUT_BCASFD_MODE                         111
#define DOCUMENT_MODE                              200
#define STUB_DOCUMENT_CONFIGURATION_MODE           201
#define CONFIG_FILE_TO_LOCO_LISTING_MODE           202


#define MANIPULATE_PROJECT_CONFIGURATION   301
#define MANIPULATE_BUILD_CONFIGURATION     302
#define MANIPULATE_DOCUMENT_CONFIGURATION  303

#define EFFECTIVE_PATHS_LOCAL   6
#define EFFECTIVE_PATHS_INSTALL 7

struct bca_context
{
 int mode, extra_args_start, manipulation_type, verbose,
     n_withouts, n_disables, n_enables, n_swaps;
 char *search_value_key, *new_value_string;
 char value_key[1024], value_string[1024];
 char *principle, *qualifier;

 char *install_prefix, *host_prefix, *build_prefix;
 char **without_strings, **disabled_components, **enabled_components,
      **swapped_components, **swapped_component_hosts;

#ifdef HAVE_CWD
 char *cwd;
#endif

 char *project_name;
 char *build_configuration_contents;
 char *project_configuration_contents;
 int build_configuration_length;
 int project_configuration_length;

#ifndef IN_SINGLE_FILE_DISTRIBUTION
 struct document_handling_context *dctx;
 int loop_inputs, pass_number;
 char *engine_name;
 char *output_type;
#endif

 char **input_files;
 int n_input_files, line_number, input_file_index;

 char *output_file;
};

struct component_details
{
 char *host;
 char *project_component;
 char *project_component_type;
 char *project_component_output_name;

 char **file_names;
 char **file_base_names;
 char **file_extensions;
 int n_file_names;

 char **inputs;
 int n_inputs;

 char **file_deps;
 int n_file_deps;

 char **lib_headers;
 int n_lib_headers;

 char **dependencies;
 int n_dependencies;

 char **include_dirs;
 int n_include_dirs;

 char **project_components;
 char **project_component_types;
 char **project_output_names;
 int n_components;

 char *major;
 char *minor;

 char **withouts;
 int n_withouts;
};

struct host_configuration
{
 /* tools */
 char *cc;                           /* C compiler */
 char *cxx;                          /* C++ compiler */
 char *python;                       /* python */
 char *erlc;                         /* erlang compiler */
 char *pkg_config;                   /* pkg-config */
 char *xgettext, *msgmerge, *msgfmt; /* gettext */

 /* flags for tools */
 char *cppflags;                           /* C & C++ preprocessor flags */
 char *cflags;                             /* generic "compiler" flags; ie pkg-config --cflags */
 char *ccflags;                            /* C compiler flags */
 char *cxxflags;                           /* C++ compiler flags */
 char *ldflags;                            /* C & C++ linker flags */
 char *cc_output_flag;                     /* C & C++ specify output filename flag (ie -o) */
 char *cc_compile_bin_obj_flag;            /* C & C++ compile object flag (ie -c) */
 char *cc_compile_shared_library_obj_flag; /* C & C++ compile shared object flag (ie -c -fpic) */
 char *cc_include_dir_flag;                /* C & C++ add include dir flag (ie -I) */
 char *cc_define_macro_flag;               /* C & C++ define preprocessor macro (ie -D) */
 char *erlc_flags;                         /* erlang compiler flags */
 char *erlc_output_dir_flag;               /* erlc change output directory (ie -o) */
 char *python_flags;                       /* python flags */

 /* output file characteristics */
 char *binary_suffix;
 char *shared_library_prefix, *shared_library_suffix;
 char *obj_suffix;

 /* input directories */
 char *pkg_config_path, *pkg_config_libdir;

 /* output directories */
 char *build_prefix;           /* prefix for run from local */
 char *install_prefix;         /* autoconf's prefix */
 char *install_bin_dir;        /* autoconf's bindir */
 char *install_lib_dir;        /* autoconf's libdir */
 char *install_include_dir;    /* autoconf's includedir */
 char *install_pkg_config_dir;
 char *install_locale_data_dir;
};

#ifndef IN_SINGLE_FILE_DISTRIBUTION
/* documents.c ---------------------------------- */
char * handle_document_functions(struct bca_context *ctx, char *key);

int document_mode(struct bca_context *ctx);

struct document_handling_context_stack_frame
{
 int (*close_function) (struct document_handling_context *, void *);
 void *data;
 int type, input_file_index, line_number;
};

#define DLEVEL_NONE     0
#define DLEVEL_DOCUMENT 1
#define DLEVEL_PART     2
#define DLEVEL_CHAPTER  3
#define DLEVEL_SECTION  4
#define DLEVEL_SUB      5
#define DLEVEL_INSET    6
#define DLEVEL_LISTING  7

#define DSTACK_TYPE_TAG   100
#define DSTACK_TYPE_TABLE 101
#define DSTACK_TYPE_TR    102
#define DSTACK_TYPE_TC    103
#define DSTACK_TYPE_LIST  104
#define DSTACK_TYPE_POINT 105

struct toc_element
{
 int type;
 int count;
 char *name;
 char page[16];
 struct toc_element *last, *next, *child, *parrent;
};

struct toc_element *new_toc_element(int type, char *name);

char *type_to_string(int type);

struct document_handling_context
{
 char *engine_name;
 char *output_type;

 struct bca_context *ctx;
 int dmode_depth;

 int table_depth, list_depth;

 int stack_depth;
 struct document_handling_context_stack_frame stack[64];

 int current_level;
 int implied_levels_mask[8];

 int tag_depth, tag_buffer_length;
 char *tags[32];
 char tag_buffer[1024];
 char *tag_datas[32];

 char input_buffer[1024];
 int input_buffer_length;

 char *document_configuration_contents;
 int document_configuration_length;

 void *document_engine_context;
 int (*start_document) (struct document_handling_context *dctx);
 int (*finish_document) (struct document_handling_context *dctx);
 int (*consume_text) (struct document_handling_context *dctx, char *text, int length);
 int (*open_point) (struct document_handling_context *dctx, char **parameters, int n_parameters);
 int (*close_point) (struct document_handling_context *dctx);
 int (*open_list) (struct document_handling_context *dctx, char **parameters, int n_parameters);
 int (*close_list) (struct document_handling_context *dctx);
 int (*open_listing) (struct document_handling_context *dctx, char **parameters, int n_parameters);
 int (*close_listing) (struct document_handling_context *dctx);
 int (*open_inset) (struct document_handling_context *dctx, char **parameters, int n_parameters);
 int (*close_inset) (struct document_handling_context *dctx);
 int (*open_subsection) (struct document_handling_context *dctx, char **parameters, int n_parameters);
 int (*close_subsection) (struct document_handling_context *dctx);
 int (*open_section) (struct document_handling_context *dctx, char **parameters, int n_parameters);
 int (*close_section) (struct document_handling_context *dctx);
 int (*open_chapter) (struct document_handling_context *dctx, char **parameters, int n_parameters);
 int (*close_chapter) (struct document_handling_context *dctx);
 int (*open_part) (struct document_handling_context *dctx, char **parameters, int n_parameters);
 int (*close_part) (struct document_handling_context *dctx);
 int (*open_table) (struct document_handling_context *dctx, char **parameters, int n_parameters);
 int (*close_table) (struct document_handling_context *dctx);
 int (*open_tr) (struct document_handling_context *dctx, char **parameters, int n_parameters);
 int (*close_tr) (struct document_handling_context *dctx);
 int (*open_tc) (struct document_handling_context *dctx, char **parameters, int n_parameters);
 int (*close_tc) (struct document_handling_context *dctx);
 int (*open_tag) (struct document_handling_context *dctx, char **parameters, int n_parameters);
 int (*close_tag) (struct document_handling_context *dctx);
};

/* plaintext.c */
int activate_document_engine_plaintext(struct document_handling_context *dctx);

int activate_document_engine_passthrough(struct document_handling_context *dctx);

int stub_document_configuration_file(struct bca_context *ctx);

int conf_lookup_int(struct document_handling_context *dctx,
                    char *key, int *value, int default_value);

int conf_lookup_string(struct document_handling_context *dctx,
                       char *key, char **value, char *default_value);

#endif

/* selftest.c ----------------------------------- */
int self_test(struct bca_context *ctx);

/* replace.c ------------------------------------ */
char *resolve_string_replace_key(struct bca_context *ctx, char *key);

int string_replace(struct bca_context *ctx);

int parse_function_parameters(char *string, char ***array, int *array_length);

char *current_file_name(struct bca_context *ctx);

/* conversions.c -------------------------------- */
char *lib_file_name_to_link_name(const char *file_name);

char *without_string_to_without_macro(struct bca_context *ctx, char *in);

int render_project_component_output_name(struct bca_context *ctx,
                                         char *host, char *component, int edition,
                                         char ***array_ptr, char ***extensions);

char *host_identifier_from_host_prefix(struct bca_context *ctx);

char *build_prefix_from_host_prefix(struct bca_context *ctx);

char *component_type_file_extension(struct bca_context *ctx, struct host_configuration *tc,
                                    char *project_component_type,
                                    char *project_component_output_name);

int file_to_C_source(struct bca_context *ctx, char *file_name);

char *file_name_to_array_name(char *file_name);

/* main.c --------------------------------------- */
struct bca_context *setup(int argc, char **argv);  // selftested

int shutdown(struct bca_context *ctx);  // selftested

void help(void);

int short_help_mode(struct bca_context *ctx);

int concatenate(struct bca_context *ctx, int argc, char **argv);

/* strings.c ------------------------------------ */
int contains_string(char *source, int source_length, char *search, int search_length);  // selftested

int add_to_string_array(char ***array, int array_size,
                        char *string, int string_length,
                        int prevent_duplicates);  // selftested

int free_string_array(char **array, int n_elements);  // selftested

int path_extract(const char *full_path, char **base_file_name, char **extension);  // selftested

char *read_file(char *name, int *length, int silent_test);  // selftested

int mmap_file(char *name, void **p, int *length, int *fd);

int umap_file(void *p, int length, int fd);

int find_line(char *buffer, int buffer_length, int *start, int *end, int *line_length); // selftested

int split_strings(struct bca_context *ctx, char *source, int length,
                  int *count, char ***strings);  // selftested

char *escape_value(struct bca_context *ctx, char *source, int length);  // selftested

int count_characters(char *buffer, int length);

int n_bytes_for_n_characters(char *buffer, int length, int n_characters);

int next_character(char *buffer, int length);

int n_bytes_for_n_characters(char *buffer, int length, int n_characters);

/* config_files.c ------------------------------- */
int iterate_key_primitives(struct bca_context *ctx, char *file, int file_length, int *offset,
                           char *principle_filter, char *component_filter, char *key_filter,
                           char principle[256], char component[256], char key[256],
                           int *equals_pos);    // selftested

char *lookup_key(struct bca_context *ctx, char *file, int file_length,
                 char *principle_filter, char *component_filter, char *key_filter);   // selftested

int list_unique_principles(struct bca_context *ctx, char *qualifier,
                           char *contents, int length,
                           char ***principle_list, int *n_principles);   // selftested

int list_unique_qualifiers(struct bca_context *ctx,
                           char *contents, int length,
                           char ***list, int *n_elements);

int output_modifications(struct bca_context *ctx, FILE *output,
                         char *contents, int length, int n_records,
                         char **principle, char **component, char **key, char **value); // selftested

int output_modification(struct bca_context *ctx, FILE *output,
                        char *contents, int length,
                        char *principle, char *component, char *key, char *value);

int modify_file(struct bca_context *ctx, char *filename,
                char *principle, char *component, char *key, char *value);

int add_value(struct bca_context *ctx);

int pull_value(struct bca_context *ctx);

int check_value_inline(struct bca_context *ctx,
                       char *contents, int length,
                       char *principle, char *qualifier,
                       char *key, char *check_value);

int check_value(struct bca_context *ctx);

int smart_add_value(struct bca_context *ctx);

int smart_pull_value(struct bca_context *ctx);

int engage_build_configuration_disables_for_host(struct bca_context *ctx, char *host);

int engage_build_configuration_swaps_for_host(struct bca_context *ctx, char *host);

int check_project_component_types(struct bca_context *ctx);

int list_project_components(struct bca_context *ctx,
                            struct component_details *cd);

int list_component_internal_dependencies(struct bca_context *ctx,
                                         struct component_details *cd,
                                         char ***list, int *n_elements);

int list_component_external_dependencies(struct bca_context *ctx,
                                         struct component_details *cd,
                                         char ***list, int *n_elements);

int list_component_opt_external_dependencies(struct bca_context *ctx,
                                             struct component_details *cd,
                                             char ***list, int *n_elements);

int resolve_project_name(struct bca_context *ctx);  // selftested

int resolve_component_dependencies(struct bca_context *ctx,
                                   struct component_details *cd);

int resolve_component_version(struct bca_context *ctx,
                              char *contents, int contents_length,
                              struct component_details *cd,
                              char *component_type,
                              char *project_component);

int resolve_component_file_dependencies(struct bca_context *ctx,
                                        struct component_details *cd,
                                        int component_index);

int resolve_component_input_dependencies(struct bca_context *ctx,
                                         struct component_details *cd,
                                         int component_index);

char *resolve_build_host_variable(struct bca_context *ctx,
                                  char *host,
                                  char *project_component,
                                  char *key);

struct host_configuration *
resolve_host_configuration(struct bca_context *ctx,
                           char *host,
                           char *component);

int free_host_configuration(struct bca_context *ctx, struct host_configuration *tc);

int resolve_effective_path_mode(struct bca_context *ctx);

int resolve_component_installation_path(struct bca_context *ctx,
                                        char *host,
                                        char *component_type,
                                        char *component,
                                        char **path);

int check_duplicate_output_names(struct bca_context *ctx, struct component_details *cd);

int is_project_using_config_h(struct bca_context *ctx);

#ifndef IN_SINGLE_FILE_DISTRIBUTION
int config_file_to_loco_listing(struct bca_context *ctx,
                                char *in_file_name,
                                char *out_file_name);
#endif

/* configure.c ---------------------------------- */
int is_c_compiler_needed(struct bca_context *ctx,
                         struct component_details *cd,
                         char **files, char **extensions, int count);

int is_cxx_compiler_needed(struct bca_context *ctx,
                           struct component_details *cd,
                           char **files, char **extensions, int count);

int is_pkg_config_needed(struct bca_context *ctx,
                         struct component_details *cd);

int test_package_exist(struct bca_context *ctx,
                       struct component_details *cd,
                       struct host_configuration *tc,
                       char *package, int optional);

int test_runnable(struct bca_context *ctx, char *command);

int configure(struct bca_context *ctx);

int append_host_configuration(struct bca_context *ctx,
                              struct host_configuration *tc,
                              struct component_details *cd,
                              int *n_modify_records,
                              char ***mod_principles,
                              char ***mod_components,
                              char ***mod_keys,
                              char ***mod_values);

int assemble_list_of_used_source_files(struct bca_context *ctx,
                                       struct component_details *cd,
                                       char ***file_list_ptr,
                                       char ***extensions_list_ptr,
                                       int *count_ptr);

int is_file_of_type_used(struct bca_context *ctx,
                         struct component_details *cd,
                         char **files, char **extensions, int count,
                         char *type_extension);

/* gmakefile.c ---------------------------------- */
int generate_gmakefile_mode(struct bca_context *ctx);

int generate_gmake_host_components(struct bca_context *ctx, FILE *output,
                                   char **hosts, int n_hosts);

int generate_gmake_clean_rules(struct bca_context *ctx, FILE *output,
                               char **hosts, int n_hosts,
                               struct component_details *cd);

int generate_gmake_host_component_file_rules(struct bca_context *ctx, FILE *output,
                                             struct component_details *cd);

int generate_gmake_install_rules(struct bca_context *ctx, FILE *output,
                                 char **hosts, int n_build_hosts,
                                 int uninstall_version);

int generate_create_tarball_rules(struct bca_context *ctx, FILE *output);

int count_host_component_target_dependencies(struct bca_context *ctx,
                                             struct component_details *cd);

/* graphviz.c ----------------------------------- */
int graphviz_edges(struct bca_context *ctx, FILE *output,
                   struct component_details *cd);

int graphviz_nodes(struct bca_context *ctx, FILE *output,
                   char **hosts, int n_build_hosts,
                   struct component_details *cd);

int generate_graphviz_mode(struct bca_context *ctx);

int graphviz_string_clean(struct bca_context *ctx,
                          char *input, int length,
                          char *output, int size);

/* newt.c --------------------------------------- */
#ifndef WITHOUT_LIBNEWT
int newt_interface(struct bca_context *ctx);
#endif

/* gtk.c ---------------------------------------- */
#ifdef HAVE_GTK
int gtk_interface(struct bca_context *ctx);
#endif

/* embedded_files.c ----------------------------- */
extern const int __configure_length;
extern const char __configure[];

extern const int bca_sfd_c_length;
extern const char bca_sfd_c[];

/* utf8_word_engine.c ----------------------------- */
#define UWC_WORD 1
#define UWC_BROKEN_WORD 2

struct unicode_word_context
{
 unsigned char character_buffer[7];
 char word_buffer[256];
 int buffer_size, buffer_length, n_characters;
 int direction, character_buffer_length, expected_character_length;

 void *data;
 int (*consume_word) (struct unicode_word_context *uwc, void *data, int flags);

 char *suffix;
 int suffix_buffer_length;
};

struct unicode_word_context *
unicode_word_engine_initialize(void *data,
                               int (*consume_word) (struct unicode_word_context *uwc,
                                                    void *data, int flags));

int unicode_word_engine_finalize(struct unicode_word_context *uwc);

int unicode_word_engine_consume_byte(struct unicode_word_context *uwc, unsigned char byte);

int is_white_space(char *utf8_character);

int unicode_word_engine_suffix(struct unicode_word_context *uwc, char *buffer, int buffer_length);

/* hyphenation_engine.c -------------------- */

struct hyphenation_context;

struct hyphenation_context *
hyphenation_engine_initialize(char *language);

int hyphenation_engine_finalize(struct hyphenation_context *hc);

int hyphenation_engine_attempt(struct hyphenation_context *hc, int fit_size,
                               struct unicode_word_context *source,
                               struct unicode_word_context *first,
                               struct unicode_word_context *second);

#endif

