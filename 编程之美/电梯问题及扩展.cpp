/**
 *  ÿ�ε��ݴ�һ¥������ʱ������ֻ�������ͣ�����е�ĳһ�㡣���еĳ˿Ͷ���һ¥�ϵ��ݣ�����ĳ¥��󣬵���
 *  ͣ���������г˿��ٴ�������¥�ݵ��Լ���Ŀ�Ĳ㡣
 *  �ʣ�����ͣ����һ�㣬�ܹ���֤��γ������ݵ����г˿���¥�ݵĲ���֮�����١�
 */
// passenger����������Ӧ�����¥��������0��Ӧ0�㣬����
int liftWorker(vector<int> &passengers)
{
    if (passengers.size() < 2) {
        return 1;
    }
    // N1�����¥�����µĳ˿�������N3�����¥�����ϵĳ˿�����
    int N1 = 0, N2 = passengers[1], N3 = 0;
    for (int i = 2; i < passengers.size(); ++i) {
        N3 += passengers[i];
    }
    int bestFloor = 1;
    for (int i = 2; i < passengers.size(); ++i) {
        if (N3 > N1 + N2) {
            bestFloor = i;
            N1 += N2;
            N2 = passengers[i];
            N3 -= N2;
        }
        else break;
    }
    return bestFloor;
}

/**
 *  ������չ1�������ݿ���ͣ��K��¥�㣬Ӧ��ͣ���ļ���¥�㣿
 *  ����ͣ��1��j¥��ͣ��K-1�Σ���j + 1��n��ͣ��1�Σ���̬�滮����
 */
// �ӵ�x�㵽y������ͣ������Ҫ�ߵ�¥����
pair<int, int> liftWorker(vector<int> &passengers, int x, int y)
{
    int N1 = 0, N2 = passengers[x], N3 = 0, walkSum = 0;
    for (int i = x + 1; i <= y; ++i) {
        N3 += passengers[i];
        walkSum += passengers[i] * (i - x);
    }
    int bestfloor = x;
    for (int i = x + 1; i <= y; ++i) {
        if (N3 > N1 + N2) {
            bestfloor = i;
            walkSum -= N3 - (N1 + N2);
            N1 += N2;
            N2 = passengers[i];
            N3 -= N2;
        }
        else break;
    }
    return make_pair(walkSum, bestfloor);
}

vector<int> K_lift(vector<int> &passengers, int K)
{
    vector<int> re;
    // �߽��������
    if (passengers.size() <= K + 1) {
        for (int i = 1; i < passengers.size(); ++i) {
            re.push_back(i);
        }
    }
    int n = passengers.size(), A[n][n], Lift[n][n];
    pair<int, int> B[n][n];
    // Ԥ����
    for (int i = 1; i < n; ++i) {
        for (int j = i; j < n; ++j) {
            B[i][j] = liftWorker(passengers, i, j);
        }
    }
    for (int i = 1; i < n; ++j) {
        A[i][1] = B[1][j];
        for (int j = 2; j <= i; ++j) {
            A[i][j] = INT_MAX;
            for (int q = j - 1; q < i; ++q) {
                int tmp = A[q][j - 1] + B[q + 1][i].first;
                if (tmp < A[i][j]) {
                    Lift[i][j] = q;
                    A[i][j] = tmp;
                }
            }
        }
    }
    // ������
    for (int q = K, p = n - 1, tmp; q >= 1; --q) {
        tmp = Lift[p][q];
        re.push_back(B[tmp + 1][p].second);
        p = tmp;
    }
    return re;
}

/**
 *  ������չ2����������̾�������
 *  12�������ֲ���һ����������ٹ�·�����࣬�������빫·�����˵ľ���ֱ���0��4��5��10��12��18��27��30��31��38��39��47.
 *  ����12��������ѡȡ3��ԭ�Ϲ�Ӧ����ʹ��ʣ�๤���������ԭ�Ϲ�Ӧ������֮����̣���Ӧ��ѡ�������� ��
 *
 *  ��̬�滮����
 *  ��i��j��ѡ��p����������̾�����ڴ�i��kѡ��p - 1�������ļ��ϴ�k��jѡ��һ�������ľ�����Сֵ
 */
int MinDistanceOfOne(vector<int> &ls, int l, int r)
{
    if (l < r) {
        return -1;
    }
    int m = (l + r) / 2;
    int re = 0;
    for (int i = l; i <= r; ++i) {
        re += abs(ls[m] - ls[i]);
    }
    return re;
}

vector<int> MinDistance(vector<int> &ls, int facts)
{
    int n = ls.size(), A[n + 1][n + 1], B[n + 1][n + 1], fac[n + 1][n + 1];
    for (int i = 1; i <= n; ++i) {
        for (int j = i; j <= n; ++j) {
            B[i][j] = MinDistanceOfOne(ls, i, j);
        }
    }
    for (int i = 1; i <= n; ++i) {
        A[i][1] = B[1][i];
        for (int j = 2; j <= i; ++j) {
            A[i][j] = INT_MAX;
            for (int k = j - 1; k < i; ++k) {
                int curmin = A[k][j - 1] + B[k + 1][j];
                if (curmin < A[i][j]) {
                    A[i][j] = curmin;
                    fac[i][j] = k;
                }
            }
        }
    }
    // ������
    vector<int> re;
    for (int q = facts, p = n, tmp; q >= 1; --q) {
        tmp = fact[p][q];
        re.push_back((tmp + 1 + p) / 2);
        p = tmp;
    }
    return re;
}
