import java.util.*;
import java.io.*;


class SimpsonIntegration {
	public SimpsonIntegration() {
		super();
	}

    public double Simpson(Function f, double a, double b, int n) {
        double s1, s2;
        int i;

        double step = (b - a) / n;
        s1 = s2 = 0;
        for (i = 1; i < n; i++) {
            s2 += f.Func(a + step * i);   //xi���
        }
        for (i = 1; i <= n; i++) {
            s1 += f.Func(a + step * i - step / 2);  //��xi - step/2�� ���
        }

        double s = step * (f.Func(a) + f.Func(b) + 4 * s1 + 2 * s2) / 6.0;

        return s;
    }

    public double VsSimpson(Function f, double a, double b, double eps)  {
        int n = 1;   //��ʼ�ָ�һ��������
        double s1 = (b - a) * (f.Func(a) + f.Func(b) + 4 * f.Func((a + b) / 2.0)) / 6.0; //�����ʼ���ε����
        double diff = eps + 1.0;
        do  {
            n = 2 * n;    //���ηָ�ӱ�
            double t = Simpson(f, a, b, n);
            diff = Math.abs(s1 - t);      //�������ε����Ľ����ֵ
            s1 = t;
        } while (diff >= eps);

        return s1;
    }

}
