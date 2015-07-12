package com.manager.util;

import java.lang.reflect.Field;

import java.text.DateFormat;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.Map;

import javax.servlet.http.HttpServletRequest;

public class ObjectFactory {

	public static <T> T newInstance(HttpServletRequest request,Class cla){
		Object obj=null;
		try {
			obj=cla.newInstance();
			Field[] fields=cla.getDeclaredFields();
			Map map=request.getParameterMap();
			for (Field f : fields) {
				String name=f.getName();
				String[] v=(String[])map.get(name);
				if(v==null){
					continue;
				}
				f.setAccessible(true);
				Class type=f.getType();
				if(type.isArray()){
					f.set(obj, v);
				}else{
					if(type==int.class || type==Integer.class){
						f.set(obj, Integer.parseInt(v[0]));
					}else if(type==double.class||type==Double.class){
						f.set(obj, Double.parseDouble(v[0]));
					}else if(type==long.class||type==Long.class){
						f.set(obj, Long.parseLong(v[0]));
					}else if(type==Date.class)
					{
						DateFormat fmt =new SimpleDateFormat("yyyy/MM/dd HH:mm:ss");    
				        Date date = fmt.parse(v[0]);
						f.set(obj, fmt.format(date));
					}else{
						f.set(obj, (String)v[0]);
					}
				}
			}
		} catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		return (T)obj;
	}
	
}
