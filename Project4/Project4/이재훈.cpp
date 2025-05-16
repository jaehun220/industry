#define STRING_SIZE 12800

int i_strlen(const char* s)
{
	int i = 0;
	while (s[i])
		i++;
	return i;
}

void reverse(char* s, int len)
{
	for (int i = 0; i < len / 2; i++)
	{
		char tmp = s[i];
		s[i] = s[len - 1 - i];
		s[len - 1 - i] = tmp;
	}
}

int is_a_ge_b(const char* a, int la, const char* b, int lb)
{
	if (la > lb)
		return 1;
	if (la < lb)
		return 0;
	for (int i = 0; i < la; i++)
	{
		if (a[i] > b[i])
			return 1;
		if (a[i] < b[i])
			return 0;
	}
	return 1;
}

void add26(const char* a, int la, const char* b, int lb, char* res, int* res_len)
{
	int carry = 0;
	int i = 0;
	while (i < la || i < lb || carry)
	{
		int digit_a = (i < la) ? a[i] - 'A' : 0;
		int digit_b = (i < lb) ? b[i] - 'A' : 0;
		int sum = digit_a + digit_b + carry;
		res[i] = (sum % 26) + 'A';
		carry = sum / 26;
		i++;
	}
	*res_len = i;
}

void sub26(const char* a, int la, const char* b, int lb, char* res, int* res_len)
{
	int borrow = 0;
	int i = 0;
	while (i < la)
	{
		int digit_a = a[i] - 'A';
		int digit_b = (i < lb) ? b[i] - 'A' : 0;
		int sub = digit_a - digit_b - borrow;
		if (sub < 0)
		{
			sub += 26;
			borrow = 1;
		}
		else
			borrow = 0;

		res[i] = sub + 'A';
		i++;
	}
	while (i > 1 && res[i - 1] == 'A')
		i--;
	*res_len = i;
}

void test_main(char answer[STRING_SIZE], const char question[STRING_SIZE])
{
	char res[STRING_SIZE];
	int res_len = 0;
	int res_sign = 0; 

	char term[STRING_SIZE];
	int term_len;
	char op;

	int i = 0;
	int qlen = i_strlen(question);

	int ti = 0;
	res_sign = 0;

	if (question[i] == '-')
	{
		res_sign = 1;
		i++;
	}
	else if (question[i] == '+')
		i++;

	while (i < qlen && question[i] != '+' && question[i] != '-')
		term[ti++] = question[i++];
	term[ti] = '\0';
	term_len = ti;

	reverse(term, term_len);

	for (int k = 0; k < term_len; k++)
		res[k] = term[k];
	res_len = term_len;

	while (i < qlen)
	{
		op = question[i++];
		ti = 0;
		while (i < qlen && question[i] != '+' && question[i] != '-')
			term[ti++] = question[i++];
		term[ti] = '\0';
		term_len = ti;

		reverse(term, term_len);

		if (res_sign == 0) 
		{
			if (op == '+')
			{
				add26(res, res_len, term, term_len, res, &res_len);
			}
			else 
			{
				if (is_a_ge_b(res, res_len, term, term_len))
					sub26(res, res_len, term, term_len, res, &res_len);
				else
				{
					sub26(term, term_len, res, res_len, res, &res_len);
					res_sign = 1;
				}
			}
		}
		else
		{
			if (op == '+')
			{
				if (is_a_ge_b(term, term_len, res, res_len))
				{
					sub26(term, term_len, res, res_len, res, &res_len);
					res_sign = 0;
				}
				else
					sub26(res, res_len, term, term_len, res, &res_len);
			}
			else
				add26(res, res_len, term, term_len, res, &res_len);
		}
	}

	reverse(res, res_len);

	int idx = 0;
	if (res_sign == 1)
		answer[idx++] = '-';
	for (int k = 0; k < res_len; k++)
		answer[idx++] = res[k];
	answer[idx] = '\0';
}
