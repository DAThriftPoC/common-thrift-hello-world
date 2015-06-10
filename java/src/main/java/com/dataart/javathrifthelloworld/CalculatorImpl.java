package com.dataart.javathrifthelloworld;

import org.apache.thrift.TException;

public class CalculatorImpl implements Calculator.Iface {
    @Override
    public int add(int a, int b) throws TException {
        return a + b;
    }
}
