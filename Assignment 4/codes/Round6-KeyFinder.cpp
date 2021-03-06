#include <bits/stdc++.h>

using namespace std;

using bits64 = bitset<64>;
using bits32 = bitset<32>;
using bits48 = bitset<48>;
using bits56 = bitset<56>;
using bits28 = bitset<28>;

int IP[] = {
    58, 50, 42, 34, 26, 18, 10, 2,
    60, 52, 44, 36, 28, 20, 12, 4,
    62, 54, 46, 38, 30, 22, 14, 6,
    64, 56, 48, 40, 32, 24, 16, 8,
    57, 49, 41, 33, 25, 17, 9, 1,
    59, 51, 43, 35, 27, 19, 11, 3,
    61, 53, 45, 37, 29, 21, 13, 5,
    63, 55, 47, 39, 31, 23, 15, 7};

int IP_inv[] = {
    40, 8, 48, 16, 56, 24, 64, 32,
    39, 7, 47, 15, 55, 23, 63, 31,
    38, 6, 46, 14, 54, 22, 62, 30,
    37, 5, 45, 13, 53, 21, 61, 29,
    36, 4, 44, 12, 52, 20, 60, 28,
    35, 3, 43, 11, 51, 19, 59, 27,
    34, 2, 42, 10, 50, 18, 58, 26,
    33, 1, 41, 9, 49, 17, 57, 25};

bits64 apply_ip(bits64 in, bool inv = false)
{
    bits64 out;
    for (int i = 63; i >= 0; i--)
    {
        int j = (inv ? IP_inv[63 - i] : IP[63 - i]) - 1;
        out[i] = in[63 - j];
    }
    return out;
}

pair<bits32, bits32> get_LR(bits64 in)
{
    bits32 L, R;
    for (int i = 63, j = 31; i >= 32; i--, j--)
    {
        L[j] = in[i];
        R[j] = in[i - 32];
    }
    return make_pair(L, R);
}

int E[] = {
    32, 1, 2, 3, 4, 5,
    4, 5, 6, 7, 8, 9,
    8, 9, 10, 11, 12, 13,
    12, 13, 14, 15, 16, 17,
    16, 17, 18, 19, 20, 21,
    20, 21, 22, 23, 24, 25,
    24, 25, 26, 27, 28, 29,
    28, 29, 30, 31, 32, 1};

bits48 apply_E(bits32 in)
{
    bits48 out;
    for (int i = 47; i >= 0; i--)
    {
        int j = E[47 - i] - 1;
        out[i] = in[31 - j];
    }
    return out;
}

int S1[4][16] = {
    14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7,
    0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8,
    4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0,
    15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13};

int S2[4][16] = {
    15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10,
    3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5,
    0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15,
    13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9};

int S3[4][16] = {
    10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8,
    13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1,
    13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7,
    1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12};

int S4[4][16] = {
    7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15,
    13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9,
    10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4,
    3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14};

int S5[4][16] = {
    2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9,
    14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6,
    4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14,
    11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3};

int S6[4][16] = {
    12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11,
    10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8,
    9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6,
    4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13};

int S7[4][16] = {
    4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1,
    13, 0, 11, 7, 4, 9, 1, 10, 14, 3, 5, 12, 2, 15, 8, 6,
    1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2,
    6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12};

int S8[4][16] = {
    13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7,
    1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2,
    7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8,
    2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11};

bits32 apply_S(bits48 in)
{
    bits32 out;
    int i = 47, j = 31;
    for (auto S : {S1, S2, S3, S4, S5, S6, S7, S8})
    {
        int row = 0, col = 0;
        for (int k = i - 1; k > i - 5; k--)
        {
            col = col * 2 + in[k];
        }
        row = in[i] * 2 + in[i - 5];

        bitset<4> num = S[row][col];
        for (int k = j; k >= j - 3; k--)
        {
            out[k] = num[3 - (j - k)];
        }
        i -= 6;
        j -= 4;
    }
    return out;
}

int P[] = {
    16, 7, 20, 21, 29, 12, 28, 17,
    1, 15, 23, 26, 5, 18, 31, 10,
    2, 8, 24, 14, 32, 27, 3, 9,
    19, 13, 30, 6, 22, 11, 4, 25};

int P_inv[32];

void calc_P_inv()
{
    for (int i = 0; i < 32; i++)
    {
        int to = P[i] - 1;
        P_inv[to] = i + 1;
    }
}

bits32 apply_P(bits32 in, bool inv = false)
{
    bits32 out;
    for (int i = 31; i >= 0; i--)
    {
        int j = (inv ? P_inv[31 - i] : P[31 - i]) - 1;
        out[i] = in[31 - j];
    }
    return out;
}

using bits4 = bitset<4>;
using bits6 = bitset<6>;

bits4 calc(bits6 in, int i)
{
    bits4 out;
    int cur = 0;
    for (auto S : {S1, S2, S3, S4, S5, S6, S7, S8})
    {
        if (i == cur)
        {
            int row = 0, col = 0;
            for (int k = 4; k > 0; k--)
            {
                col = col * 2 + in[k];
            }
            row = in[5] * 2 + in[0];

            bitset<4> num = S[row][col];
            for (int k = 3; k >= 0; k--)
            {
                out[k] = num[k];
            }
            return out;
        }
        cur = cur + 1;
    }
    assert(false);
    return out;
}
#define endl '\n'

int main()
{
    ifstream fin("gen_out_bits.txt");
    calc_P_inv();

    int N = 1e5;

    unordered_map<bitset<6>, int> maybe[8];

    for (int _ = 0; _ < N; _++)
    {
        bitset<32> out1L, out1R, out2L, out2R;
        fin >> out1L >> out1R >> out2L >> out2R;

        // outputs after expansion in the last round
        bitset<48> out1E = apply_E(out1L);
        bitset<48> out2E = apply_E(out2L);
        bitset<48> inxorS = (out1E ^ out2E);

        // cout << inxorS << endl;

        bitset<32> xorL = bitset<32>(0x04000000);
        bitset<32> xorP = (out1R ^ out2R ^ xorL);
        bitset<32> outxorS = apply_P(xorP, true);

        for (int i = 0; i < 8; i++)
        {
            int st = i * 6;
            for (int j = 0; j < (1 << 6); j++)
            {
                bitset<6> in1 = j;
                bitset<6> in2 = 0;
                for (int k = st; k - st < 6; k++)
                {
                    in2[5 - k + st] = (in1[5 - k + st] ^ inxorS[47 - k]);
                }
                bitset<4> out1 = calc(in1, i);
                bitset<4> out2 = calc(in2, i);
                bitset<4> got = (out1 ^ out2);
                bool ok = 1;
                for (int k = i * 4; k - i * 4 < 4; k++)
                {
                    ok &= (outxorS[31 - k] == got[3 - k + i * 4]);
                }

                if (ok)
                {
                    bitset<6> cand;
                    for (int k = st; k - st < 6; k++)
                    {
                        cand[5 - k + st] = in1[5 - k + st] ^ out1E[47 - k];
                    }
                    maybe[i][cand]++;
                }
            }
        }
    }

    bitset<48> key = 0;

    for (int i = 0; i < 8; i++)
    {
        int cur_mx = 0;
        bitset<6> ans;
        vector<int> cnts;
        for (auto [bs, cnt] : maybe[i])
        {
            cnts.push_back(cnt);
            if (cnt > cur_mx)
            {
                cur_mx = cnt;
                ans = bs;
            }
        }

        sort(cnts.begin(), cnts.end());
        reverse(cnts.begin(), cnts.end());

        key = (key << 6);
        for (int j = 0; j < 6; j++)
        {
            key[j] = ans[j];
        }

        cout << i + 1 << ' ' << ans << ' ' << cnts[0] << ' ' << cnts[1] << endl;
    }

    cout << key << endl;

    return 0;
}
