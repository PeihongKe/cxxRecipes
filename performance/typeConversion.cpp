namespace performance
{
	const char* toString(unsigned val)
	{
		static thread_local char buf[21] = { '\0' }; //// 2^64 18446744073709551615
		size_t i = 20;
		if (val)
		{
			do {
				buf[--i] = "0123456789abcdef"[val];
			} while (val /= 10);
		}
		else
		{
			buf[--i] = '0';
		}
		return &buf[i];
	}

	const char* toString(int val)
	{
		static thread_local char buf[21] = { '\0' };// −9223372036854775808 to 9223372036854775807
		size_t i = 20;
		if (val > 0)
		{
			do {
				buf[--i] = "0123456789abcdef"[val];
			} while (val /= 10);
		}
		else if (val < 0)
		{
			val = -val;
			do
			{
				buf[--i] = "0123456789abcdef"[val];
			} while (val /= 10);
			buf[--i] = '-';
		}
		else
		{
			buf[--i] = '0';
		}
		return &buf[i];
	}
}