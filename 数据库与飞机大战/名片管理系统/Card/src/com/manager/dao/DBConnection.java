package com.manager.dao;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;

import com.manager.util.ReadPro;

/**
 * 
 * ���ฺ�����ݿ�Ķ�ȡ
 *
 */
public class DBConnection {

	private static final String DRIVER_NAME;
	private static final String USER;
	private static final String PASSWORD;
	private static final String URL;
	
	
	static{
		//�������ļ��л�ȡҪ����Դ
		//�����ļ��ĸ�ʽ: name=value
		USER=ReadPro.getNewInstance().getProperty("USER");
		DRIVER_NAME=ReadPro.getNewInstance().getProperty("DRIVER_NAME");
		PASSWORD=ReadPro.getNewInstance().getProperty("PASSWORD");
		URL=ReadPro.getNewInstance().getProperty("URL");
		try {
			//��������
			Class.forName(DRIVER_NAME);
		} catch (ClassNotFoundException e) {
			e.printStackTrace();
		}
	}
	/**
	 * ��ȡ����
	 * @return
	 * @throws SQLException
	 */
	public static Connection getConnection() throws SQLException{
		Connection conn=DriverManager.getConnection(URL, USER, PASSWORD);
		return conn;
	}
	
	
	/*
	public static void main(String[] args) throws SQLException {
		Connection conn=DBConnection.getConnection();
		Statement stmt=conn.createStatement();
		stmt.executeUpdate("insert into user_info values(2,'dddd')");
		
		
	}*/
}
