#define STRING_SIZE 12800

int i_strlen(const char *s)
{
    int i = 0;
    while (s[i])
        i++;
    return i;
}

void reverse(char *s, int len)
{
    for (int i = 0; i < len / 2; i++)
    {
        char tmp = s[i];
        s[i] = s[len - 1 - i];
        s[len - 1 - i] = tmp;
    }
}

void i_strcpy(char *dst, const char *src)
{
    int i = 0;
    while ((dst[i] = src[i]))
        i++;
}

// 26의 보수 계산 + 1 (carry 반영) → dst, out_len 갱신
void complement26_with_one(char *dst, const char *src, int len, int *out_len)
{
    int carry = 1;
    for (int i = 0; i < len; i++)
    {
        int c = 'Z' - (src[i] - 'A') + carry;
        dst[i] = (c % 26) + 'A';
        carry = c / 26;
    }
    *out_len = len;
    if (carry)
    {
        dst[len] = carry + 'A';
        (*out_len)++;
    }
    dst[*out_len] = 0;
}

// acc += term (역순, LSB부터), carry 반영
void add_26(char *acc, int *len_acc, const char *term, int len_term)
{
    int carry = 0;
    int max_len = (*len_acc > len_term) ? *len_acc : len_term;
    for (int i = 0; i < max_len || carry; i++)
    {
        int a = (i < *len_acc) ? acc[i] - 'A' : 0;
        int b = (i < len_term) ? term[i] - 'A' : 0;
        int sum = a + b + carry;
        if (i < *len_acc)
            acc[i] = (sum % 26) + 'A';
        else
            acc[(*len_acc)++] = (sum % 26) + 'A';
        carry = sum / 26;
    }
    acc[*len_acc] = 0;
}

void test_main(char answer[STRING_SIZE], const char question[STRING_SIZE])
{
    char acc[STRING_SIZE] = {0}; // 누적값 (역순 저장)
    int len_acc = 0;

    int i = 0, sign = 1;
    while (question[i])
    {
        if (question[i] == '+')
        {
            sign = 1;
            i++;
        }
        else if (question[i] == '-')
        {
            sign = -1;
            i++;
        }

        char term[128] = {0};
        int len_term = 0;

        while (question[i] >= 'A' && question[i] <= 'Z')
        {
            term[len_term++] = question[i++];
        }
        term[len_term] = 0;
        reverse(term, len_term); // LSB부터 저장

        if (sign == 1)
        {
            add_26(acc, &len_acc, term, len_term);
        }
        else
        {
            char comp[129] = {0};
            int len_comp = 0;
            complement26_with_one(comp, term, len_term, &len_comp);
            add_26(acc, &len_acc, comp, len_comp);
        }
    }

    // 결과 판별: 캐리 발생 여부
    char tmp[STRING_SIZE];
    int len_tmp = len_acc;
    i_strcpy(tmp, acc);

    int is_negative = 0;
    if (acc[len_acc - 1] < 'B')
    { 
        is_negative = 1;
        reverse(tmp, len_tmp);
        complement26_with_one(tmp, tmp, len_tmp, &len_tmp);
    }
    else
    {
        reverse(tmp, len_tmp);
    }

    // 앞쪽 'A' 제거
    int start = 0;
    while (tmp[start] == 'A' && start < len_tmp - 1)
        start++;

    int pos = 0;
    if (is_negative)
        answer[pos++] = '-';
    for (int j = start; j < len_tmp; j++)
        answer[pos++] = tmp[j];
    answer[pos] = 0;
}

