#include <iostream>
#include "BinaryStore.h"
using namespace std;
//------------------------------Constructor------------------------------//
BinaryStore::BinaryStore(int len = 0)
{
      address = new char *[len];
      bytes = new char *[len];
      store = new char[len];
      for (int i = 0; i < len; i++)
      {
            address[i] = new char[5]{0};
            bytes[i] = new char[9]{0};
      }

      for (int i = 0; i < len; i++)
            store[i] = '1';
      no = len;
}
//-----------------------------------------------------------------//
//---------------------------Add address---------------------------//
//-----------------------------------------------------------------//
void BinaryStore::add_Address(char *s)
{
      int i = 0;
      while (address[i][0] != '\0')
            i++;

      for (int j = 0; j < 5; j++)
            address[i][j] = s[j];
}
//-----------------------------------------------------------------//
//------------------------------Set byte---------------------------//
//-----------------------------------------------------------------//
void BinaryStore::set_Byte(char *address, char *value)
{

      int count = 0;
      bool found = false;
      for (int i = 0; i < no; i++)
      {
            count = 0;
            for (int j = 0; address[j] != '\0'; j++)
                  if (this->address[i][j] != address[j])
                        break;
                  else
                        count++;

            if (count == 4)
            {
                  for (int j = 0; value[j] != '\0'; j++)
                  {
                        this->bytes[i][j] = value[j];
                        // cout<<bytes[i][j];
                  }

                  return;
            }
      }

      int index = 0;
      for (; index < no; index++)
      {
            if (this->address[index][0] == '\0')
            {
                  found = true;
                  break;
            }
      }
      if (found)
      {

            for (int i = 0; i < 5; i++)
            {
                  this->address[index][i] = address[i];
                  // cout<<this->address[index][i];
            }

            for (int i = 0; i < 9; i++)
            {
                  this->bytes[index][i] = value[i];
                  // cout<<this->bytes[index][i];
            }

            return;
      }

      index = no - 1;

      for (int i = 0; i < 5; i++)
      {
            this->address[index][i] = address[i];
            // cout<<this->address[index][i];
      }

      for (int i = 0; i < 9; i++)
      {
            this->bytes[index][i] = value[i];
            // cout<<this->bytes[index][i];
      }

}
//-----------------------------------------------------------------//
//------------------------------Getter-----------------------------//
//-----------------------------------------------------------------//
char *BinaryStore::Get(char *address)
{
      int count = 0;
      for (int i = 0; i < no; i++)
      {
            count = 0;
            for (int j = 0; address[j] != '\0'; j++)
                  if (this->address[i][j] == address[j])
                  {
                        count++;
                  }

                  else
                  {
                        count = 0;
                        break;
                  }

            if (count == 4)
            {

                  if (this->bytes[i][0] == '\0')
                        return nullptr;

                  else
                        return this->bytes[i];
            }
      }

      return nullptr;
}
//-----------------------------------------------------------------//
//------------------------------Equality---------------------------//
//-----------------------------------------------------------------//
bool BinaryStore::comp_EQUAL(char *a, char *b)
{
      for (int i = 0; i < 9; i++)
            if (a[i] != b[i])
                  return false;

      return true;
}
//-----------------------------------------------------------------//
//------------------------------Addition---------------------------//
//-----------------------------------------------------------------//
char *BinaryStore::Add(char *a, char *b)
{
      char *result = new char[9]{'\0'};
      result[8] = '\0';
      char carry = '0';
      for (int i = 7; i >= 0; i--)
      {
            if ((a[i] == '1' && b[i] == '0') || (a[i] == '0' && b[i] == '1'))
            {
                  if (carry == '1')
                        result[i] = '0';
                  else
                        result[i] = '1';
            }
            else if (a[i] == '1' && b[i] == '1')
            {
                  if (carry == '1')
                        result[i] = '1';
                  else
                  {
                        result[i] = '0';
                        carry = '1';
                  }
            }
            else if (a[i] == '0' && b[i] == '0')
            {
                  if (carry == '1')
                  {
                        result[i] = '1';
                        carry = '0';
                  }
                  else
                        result[i] = '0';
            }
      }

      return result;
}
//-----------------------------------------------------------------//
//------------------------------- OR ------------------------------//
//-----------------------------------------------------------------//
char *BinaryStore::comp_OR(char *a, char *b)
{
      char *result = new char[9]{'\0'};
      result[8] = '\0';
      for (int i = 0; i < 9; i++)
      {
            if ((a[i] == '1' && b[i] == '0') || (a[i] == '0' && b[i] == '1'))
                  result[i] = '1';
            else if (a[i] == '0' && b[i] == '0')
                  result[i] = '0';
            else if (a[i] == '1' && b[i] == '1')
                  result[i] = '1';
      }
      return result;
}
//-----------------------------------------------------------------//
//------------------------------- AND -----------------------------//
//-----------------------------------------------------------------//
char *BinaryStore::comp_AND(char *a, char *b)
{
      char *result = new char[9]{'\0'};
      result[8] = '\0';
      for (int i = 0; i < 9; i++)
      {
            if (a[i] == '1' && b[i] == '1')
                  result[i] = '1';
            else if (a[i] == '0' || b[i] == '0' || (a[i] == '1' && b[i] == '0') || (a[i] == '0' && b[i] == '1'))
                  result[i] = '0';
      }

      return result;
}
//-----------------------------------------------------------------//
//------------------------------- NOT -----------------------------//
//-----------------------------------------------------------------//
char *BinaryStore::comp_NOT(char *a)
{
      char *result = new char[9];
      result[8] = '\0';
      for (int i = 0; i < 9; i++)
      {
            if (a[i] == '1')
                  result[i] = '0';
            else if (a[i] == '0')
                  result[i] = '1';
      }

      return result;
}
//-----------------------------------------------------------------//
char *BinaryStore::ToString()
{
      return store;
}
//-----------------------------------------------------------------//
//--------------------------- Destructor --------------------------//
//-----------------------------------------------------------------//
BinaryStore::~BinaryStore()
{
      for (int i = 0; i < no; i++)
      {
            delete[] address[i];
            delete[] bytes[i];
      }
      delete[] address;
      delete[] bytes;
      delete[] store;
      address = 0;
      bytes = 0;
}
//----------------------------------------------------------------------//
// int main()
// {
//       return 0;
// }