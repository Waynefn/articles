long long pow_mod(long long a, int b, int r) {
	int ans = 1;
	a = a % r;
	while (b != 0) {
		if (b & 1)ans = (ans*a) % r;
		b >>= 1;
		a = (a%r)*(a%r) % r;
	}
	return ans;
}

bool ptest(int  n, int  a, int d)
{
	if (n == 2) return true;
	if (n == a || !(n & 1)) return false;
	while (!(d & 1)) d >>= 1;
	long long t = pow_mod(a, d, n);
	while (d != n - 1 && t != n - 1 && t != 1) {
		t = (t%n)*(t%n) % n;
		d <<= 1;
	}
	return t == n - 1 || (d & 1) == 1;
}

bool milonger_rabin(unsigned int n)
{
	int a[] = { 2, 7,61 };
	for (int i = 0; i < 3; i++) {
		if (n == a[i]) return true;
		if (!ptest(n, a[i], n - 1)) return false;
	}
	return true;
}
