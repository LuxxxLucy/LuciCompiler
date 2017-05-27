/* function prototype from prabsyn.c */
void indent(FILE *out, int d);
void pr_oper(FILE *out, A_oper d);
void pr_exp(FILE *out, A_exp v, int d);
void pr_var(FILE *out, A_var v, int d);
void pr_dec(FILE *out, A_dec v, int d);
void pr_ty(FILE *out, A_ty v, int d);
void pr_field(FILE *out, A_field v, int d);
void pr_fieldList(FILE *out, A_fieldList v, int d);
void pr_expList(FILE *out, A_expList v, int d);
void pr_fundec(FILE *out, A_fundec v, int d);
void pr_fundecList(FILE *out, A_fundecList v, int d);
void pr_decList(FILE *out, A_decList v, int d);
void pr_namety(FILE *out, A_namety v, int d);
void pr_nametyList(FILE *out, A_nametyList v, int d);
void pr_efield(FILE *out, A_efield v, int d);
void pr_efieldList(FILE *out, A_efieldList v, int d);
