package com.manager.util;

import java.io.UnsupportedEncodingException;

public class StrConvert {
	public static String ToCN(String str)
	{
		String strcn = null;
		try {
			strcn = new String(str.getBytes("iso-8859-1"),"utf-8");
		} catch (UnsupportedEncodingException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		return strcn;
	}
}
