import java.util.*;
import java.io.*;


class Jacobi {
	public Jacobi() {
		super();
	}

    public void JacobiEqn(double a[][], double b[], int n, double x[])   {
        double[] xt = new double[n];
        double max_diff = 0.0;
        do {
            for (int i = 0; i < n; i++) {
                double sum = 0.0;
                for (int k = 0; k < n; k++) {
                    //�Խ���Ԫ�ز�����
                    if (i != k)  {
                        sum += a[i][k] * x[k];
                    }
                }
                xt[i] = (b[i] - sum) / a[i][i];   //���ݹ�ϵ����xi����ֵ
            }

            max_diff = CalcMaxDiff(xt, x, n);

            for (int j = 0; j < n; j++)  {
                x[j] = xt[j]; //����x��׼����һ�ε���
            }
        } while (max_diff > EqConst.PRECISION);
    }

    private double CalcMaxDiff(double xt[], double x[], int n) {
        double max_diff = Math.abs(xt[0] - x[0]);
        for (int i = 1; i < n; i++) {
            double diff = Math.abs(xt[i] - x[i]);
            if (diff > max_diff) {
                max_diff = diff;
            }
        }

        return max_diff;
    }

}
