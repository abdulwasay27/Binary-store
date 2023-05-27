class BinaryStore
{

      char **address, **bytes, *store;
      int no;
public:
      BinaryStore(int len);
      void add_Address(char * s);
      void set_Byte(char *address, char *value);

      char *ToString();
      char *Add(char *a, char *b);
      char* Get(char* address);

      bool comp_EQUAL(char *a, char *b);
      char *comp_AND(char *a, char *b);
      char *comp_OR(char *a, char *b);
      char *comp_NOT(char *a);

       ~BinaryStore();
};
