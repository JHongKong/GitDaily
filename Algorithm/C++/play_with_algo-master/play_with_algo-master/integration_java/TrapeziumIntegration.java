import java.util.*;
import java.io.*;


class TrapeziumIntegration {
	public TrapeziumIntegration() {
		super();
	}

    public double Trapezium(Function f, double a, double b, int n) {
        double step = (b - a) / n;
        double sum = (f.Func(a) + f.Func(b)) / 2.0;

        for (int j = 1; j < n; j++) {
            double xj = a + j * step;
            sum = sum + f.Func(xj);
        }

        sum *= step;

        return sum;
    }

    public double VsTrapezium(Function f, double a, double b, double eps)  {
        int n = 1;   //��ʼ�ָ�һ��������
        double t1 = (b - a) * (f.Func(a) + f.Func(b)) / 2.0; //�����ʼ���ε����
        double diff = eps + 1.0;
        do {
            n = 2 * n;    //���ηָ�ӱ�
            double t = Trapezium(f, a, b, n);
            diff = Math.abs(t1 - t);      //�������ε����Ľ����ֵ
            t1 = t;
        } while (diff >= eps);

        return t1;
    }


}
