#include "fmt.h"

size_t fmt_escapecharxml(char* dest,uint32_t ch) {
  char a[FMT_LONG], b[FMT_XLONG];
  const char* s;
  size_t i,j;
  switch (ch) {
  case '&': s="&amp;"; goto string;
  case '<': s="&lt;"; goto string;
  case '>': s="&gt;"; goto string;
  case '\'': s="&apos;"; goto string;
  case '"': s="&quot;"; goto string;
  default:
    a[i=fmt_ulong(a,ch)]=0;
    b[0]='x';
    b[j=fmt_xlong(b+1,ch)+1]=0;
    s=a;
    if (i>j) { s=b; i=j; }
    if (dest) {
      dest[0]='&';
      dest[1]='#';
      byte_copy(dest+2,i,s);
      dest[i+2]=';';
    }
    return i+3;
  }
string:
  return fmt_str(dest,s);
}


#   if defined __GNUC__ && __GNUC__ > 3 && !defined __APPLE__
#       define LOWFAT_ALIAS(x) __attribute__ ((weak, alias(#x)))
#   else
#       define LOWFAT_ALIAS(x)
#   endif

#ifdef __GNUC__
//# if !defined __APPLE__ && defined __GNUC__ && __GNUC__ > 3
//size_t fmt_escapecharhtml(char* dest,uint32_t ch) __attribute__((__alias__("fmt_escapecharxml")));
#endif
size_t fmt_escapecharhtml(char* dest,uint32_t ch) LOWFAT_ALIAS(fmt_escapecharxml);