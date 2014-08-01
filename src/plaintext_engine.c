#include "plaintext.h"

int plaintext_consume_text(struct document_handling_context *dctx,
                           char *text, int length)
{
 struct plaintext_engine_context *pe_ctx;
 pe_ctx = (struct plaintext_engine_context *) dctx->render_engine_context;
 int i;

 for(i=0; i<length; i++)
 {
  /*  This takes us from a stream of bytes, and gives us a sequence of
      words, ignoring white space, and taking into consideration multi-byte
      UTF-8 characters. Calls here either result in failure, or invokations
      of the pe_consume_word() callback below with a word, the number of
      characters, and the number of bytes.
      (One reason it is done this way is because the word engine is intended
      to be used by all the different rendering engines.)
   */
  if(unicode_word_engine_consume_byte(pe_ctx->uwc, (unsigned char) text[i]))
  {
   fprintf(stderr, "BCA: plaintext_consume_text(): "
           "unicode_word_engine_consume_byte() failed\n");
   return 1;
  }
 }

 return 0;
}

int pe_consume_word(struct unicode_word_context *uwc, void *data, int flags)
{
 struct plaintext_engine_context *pe_ctx;
 struct plaintext_rendering_context *pr_ctx;

 pe_ctx = (struct plaintext_engine_context *) data;
 pr_ctx = pe_ctx->effective_rendering_context;

 /* we are inside some pass of the document loop, and within some
    hierchial element, and maybe within a tag stack. In all cases,
    here we simply feed a word to the current rendering context.
    The content may actually be writing text output, or it may be
    just be performing formating calculations.
 */
 return pe_advance_word(pr_ctx, uwc);
}


int plaintext_open_point(struct document_handling_context *dctx,
                         char **parameters, int n_parameters)
{
 struct plaintext_engine_context *pe_ctx;
 pe_ctx = (struct plaintext_engine_context *) dctx->render_engine_context;

 return 0;
}

int plaintext_close_point(struct document_handling_context *dctx)
{
 struct plaintext_engine_context *pe_ctx;
 pe_ctx = (struct plaintext_engine_context *) dctx->render_engine_context;

 return 0;
}

int plaintext_open_list(struct document_handling_context *dctx,
                        char **parameters, int n_parameters)
{
 struct plaintext_engine_context *pe_ctx;
 pe_ctx = (struct plaintext_engine_context *) dctx->render_engine_context;

 return 0;
}

int plaintext_close_list(struct document_handling_context *dctx)
{
 struct plaintext_engine_context *pe_ctx;
 pe_ctx = (struct plaintext_engine_context *) dctx->render_engine_context;

 return 0;
}

int plaintext_open_listing(struct document_handling_context *dctx,
                           char **parameters, int n_parameters)
{
 struct plaintext_engine_context *pe_ctx;
 pe_ctx = (struct plaintext_engine_context *) dctx->render_engine_context;

 return 0;
}

int plaintext_close_listing(struct document_handling_context *dctx)
{
 struct plaintext_engine_context *pe_ctx;
 pe_ctx = (struct plaintext_engine_context *) dctx->render_engine_context;

 return 0;
}

int plaintext_open_inset(struct document_handling_context *dctx,
                         char **parameters, int n_parameters)
{
 struct plaintext_engine_context *pe_ctx;
 pe_ctx = (struct plaintext_engine_context *) dctx->render_engine_context;

 return 0;
}

int plaintext_close_inset(struct document_handling_context *dctx)
{
 struct plaintext_engine_context *pe_ctx;
 pe_ctx = (struct plaintext_engine_context *) dctx->render_engine_context;

 return 0;
}

int plaintext_open_subsection(struct document_handling_context *dctx,
                              char **parameters, int n_parameters)
{
 struct plaintext_engine_context *pe_ctx;
 pe_ctx = (struct plaintext_engine_context *) dctx->render_engine_context;

 return 0;
}

int plaintext_close_subsection(struct document_handling_context *dctx)
{
 struct plaintext_engine_context *pe_ctx;
 pe_ctx = (struct plaintext_engine_context *) dctx->render_engine_context;

 return 0;
}

int plaintext_open_section(struct document_handling_context *dctx,
                           char **parameters, int n_parameters)
{
 struct plaintext_engine_context *pe_ctx;
 pe_ctx = (struct plaintext_engine_context *) dctx->render_engine_context;

 return 0;
}

int plaintext_close_section(struct document_handling_context *dctx)
{
 struct plaintext_engine_context *pe_ctx;
 pe_ctx = (struct plaintext_engine_context *) dctx->render_engine_context;

 return 0;
}

int plaintext_open_chapter(struct document_handling_context *dctx,
                           char **parameters, int n_parameters)
{
 struct plaintext_engine_context *pe_ctx;
 pe_ctx = (struct plaintext_engine_context *) dctx->render_engine_context;

 return 0;
}

int plaintext_close_chapter(struct document_handling_context *dctx)
{
 struct plaintext_engine_context *pe_ctx;
 pe_ctx = (struct plaintext_engine_context *) dctx->render_engine_context;

 return 0;
}


int plaintext_open_part(struct document_handling_context *dctx,
                        char **parameters, int n_parameters)
{
 struct plaintext_engine_context *pe_ctx;
 char *part_name = NULL;

 pe_ctx = (struct plaintext_engine_context *) dctx->render_engine_context;

 if(n_parameters == 2)
  part_name = parameters[1];

 if(dctx->ctx->pass_number == 0)
 {
  if(plaintext_add_toc_element(pe_ctx, DLEVEL_PART, part_name))
   return 1;
 }


 return 0;
}

int plaintext_close_part(struct document_handling_context *dctx)
{
 struct plaintext_engine_context *pe_ctx;
 pe_ctx = (struct plaintext_engine_context *) dctx->render_engine_context;

 return 0;
}

int plaintext_open_table(struct document_handling_context *dctx,
                         char **parameters, int n_parameters)
{
 struct plaintext_engine_context *pe_ctx;
 pe_ctx = (struct plaintext_engine_context *) dctx->render_engine_context;

 return 0;
}

int plaintext_close_table(struct document_handling_context *dctx)
{
 struct plaintext_engine_context *pe_ctx;
 pe_ctx = (struct plaintext_engine_context *) dctx->render_engine_context;

 return 0;
}

int plaintext_open_tr(struct document_handling_context *dctx,
                      char **parameters, int n_parameters)
{
 struct plaintext_engine_context *pe_ctx;
 pe_ctx = (struct plaintext_engine_context *) dctx->render_engine_context;

 return 0;
}

int plaintext_close_tr(struct document_handling_context *dctx)
{
 struct plaintext_engine_context *pe_ctx;
 pe_ctx = (struct plaintext_engine_context *) dctx->render_engine_context;

 return 0;
}

int plaintext_open_tc(struct document_handling_context *dctx,
                      char **parameters, int n_parameters)
{
 struct plaintext_engine_context *pe_ctx;
 pe_ctx = (struct plaintext_engine_context *) dctx->render_engine_context;

 return 0;
}

int plaintext_close_tc(struct document_handling_context *dctx)
{
 struct plaintext_engine_context *pe_ctx;
 pe_ctx = (struct plaintext_engine_context *) dctx->render_engine_context;

 return 0;
}

int plaintext_open_tag(struct document_handling_context *dctx,
                       char **parameters, int n_parameters)
{
 struct plaintext_engine_context *pe_ctx;
 char *tag_name;

 pe_ctx = (struct plaintext_engine_context *) dctx->render_engine_context;
 tag_name = dctx->tags[dctx->tag_depth - 1];

 if(strcmp(tag_name, "p") == 0)
  return plaintext_paragraph_open(pe_ctx);

 fprintf(stderr,
         "BCA: plaintext_open_tag(): warning, plain text engine does "
         "not support tag '%s'.\n",
         tag_name);

 return 0;
}

int plaintext_close_tag(struct document_handling_context *dctx)
{
 struct plaintext_engine_context *pe_ctx;
 char *tag_name;

 pe_ctx = (struct plaintext_engine_context *) dctx->render_engine_context;
 tag_name = dctx->tags[dctx->tag_depth - 1];

 if(strcmp(tag_name, "p") == 0)
  return plaintext_paragraph_close(pe_ctx);

 return 0;
}

int plaintext_start_document(struct document_handling_context *dctx)
{
 struct plaintext_engine_context *pe_ctx;
 int allocation_size;

 /* _start_document() is called on each loop */
 switch(dctx->ctx->pass_number)
 {
  case 0:
       if(dctx->render_engine_context != NULL)
       {
        fprintf(stderr, "BCA: plaintex_start_document(): render engine should not be initialized "
                " on start of first pass\n");
        return 1;
       }

       allocation_size = sizeof(struct plaintext_engine_context);
       if((pe_ctx = (struct plaintext_engine_context *)
                    malloc(allocation_size)) == NULL)
       {
        fprintf(stderr, "BCA: malloc(%d) failed, %s\n",
                allocation_size, strerror(errno));
        return 1;
       }

       memset(pe_ctx, 0, allocation_size);
       pe_ctx->dctx = dctx;
       if((pe_ctx->uwc =
           unicode_word_engine_initialize(pe_ctx,
                                          pe_consume_word)) == NULL)
       {
        fprintf(stderr,
                "BCA: plaintext_start_document(): unicode_word_engine_initialize() failed.\n");
        free(pe_ctx);
        return 1;
       }

       pe_ctx->paragraph_line_spacing = 1;
       pe_ctx->paragraph_indent = 4;
       pe_ctx->show_toc = 1;
       dctx->render_engine_context = pe_ctx;

       pe_ctx->current_column = 0;
       pe_ctx->current_row = 0;
       pe_ctx->current_page = 0;




       break;

  case 1:
       if((pe_ctx = (struct plaintext_engine_context *)
                     dctx->render_engine_context) == NULL)
       {
        fprintf(stderr, "BCA: plaintex_start_document(): render engine should have been initialized "
                " on start of first pass\n");
        return 1;
       }

       pe_ctx->current_column = 0;
       pe_ctx->current_row = 0;
       pe_ctx->current_page = 0;

       if(pe_ctx->show_toc == 1)
        if(pe_print_toc(pe_ctx))
         return 1;
       break;

  default:
       fprintf(stderr,
               "BCA: plaintext_start_document(): I should not have a pass %d\n",
               dctx->ctx->pass_number);
       return 1;
 }

 return 0;
}

int plaintext_finish_document(struct document_handling_context *dctx)
{
 struct plaintext_engine_context *pe_ctx;
 pe_ctx = (struct plaintext_engine_context *) dctx->render_engine_context;

 if(pe_advance_line(pe_ctx))
  return 1;

 switch(dctx->ctx->pass_number)
 {
  case 0:
       /* proceede to next pass */
       dctx->ctx->loop_inputs = 1;
       break;

  case 1:
       /* we're done. shutdown */
       unicode_word_engine_finalize(pe_ctx->uwc);
       break;

  default:
       fprintf(stderr,
               "BCA: plaintext_finish_document(): I should not have a pass %d\n",
               dctx->ctx->pass_number);
       return 1;
 }

 return 0;
}

int activate_document_engine_plaintext(struct document_handling_context *dctx)
{
 dctx->start_document = plaintext_start_document;
 dctx->finish_document = plaintext_finish_document;
 dctx->consume_text = plaintext_consume_text;
 dctx->open_point = plaintext_open_point;
 dctx->close_point = plaintext_close_point;
 dctx->open_list = plaintext_open_list;
 dctx->close_list = plaintext_close_list;
 dctx->open_listing = plaintext_open_listing;
 dctx->close_listing = plaintext_close_listing;
 dctx->open_inset = plaintext_open_inset;
 dctx->close_inset = plaintext_close_inset;
 dctx->open_subsection = plaintext_open_subsection;
 dctx->close_subsection = plaintext_close_subsection;
 dctx->open_section = plaintext_open_section;
 dctx->close_section = plaintext_close_section;
 dctx->open_chapter = plaintext_open_chapter;
 dctx->close_chapter = plaintext_close_chapter;
 dctx->open_part = plaintext_open_part;
 dctx->close_part = plaintext_close_part;
 dctx->open_table = plaintext_open_table;
 dctx->close_table = plaintext_close_table;
 dctx->open_tr = plaintext_open_tr;
 dctx->close_tr = plaintext_close_tr;
 dctx->open_tc = plaintext_open_tc;
 dctx->close_tc = plaintext_close_tc;
 dctx->open_tag = plaintext_open_tag;
 dctx->close_tag = plaintext_close_tag;

 return 0;
}