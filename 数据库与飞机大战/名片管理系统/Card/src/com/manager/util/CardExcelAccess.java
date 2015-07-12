package com.manager.util;
/*出账导出excel表*/
import java.sql.Connection;
import java.sql.ResultSetMetaData;
import java.sql.SQLException;
import java.sql.Statement;
import java.sql.ResultSet;
import java.sql.DriverManager;
import java.util.Collection;
import java.util.Date;
import java.util.HashMap;
import java.util.Iterator;

public class CardExcelAccess {
	/** db connection */
	private Connection c;
	/** db statement */
	private Statement stmnt;
	/** JDBC driver name */
	private String driver;
	/** url of the db */
	private String url;
	/** username to access the db */
	private String username;
	/** password for the username */
	private String password;

	/** default constructor */
	public CardExcelAccess() {
		driver = "sun.jdbc.odbc.JdbcOdbcDriver";
		url = "jdbc:odbc:card";
		username = "";
		password = "";
	}

	/**
	 * constructor with specified parameters
	 */
	public CardExcelAccess(String driver, String url, String username,
			String password) {
		this.driver = driver;
		this.url = url;
		this.username = username;
		this.password = password;
	}

	/**
	 * open the connection
	 * 
	 * @return true if opened, false otherwise
	 */
	public boolean openConnection() {
		try {
			Class.forName(driver);
			c = DriverManager.getConnection(url, username, password);
			stmnt = c.createStatement();
		} catch (Exception e) {
			e.printStackTrace();
			return false;
		}
		return true;
	}

	/**
	 * Function 2: insert a new record into the database
	 * 
	 * @return 1 if the record be inserted, 0 otherwise
	 */
	public int insertEmpInfo(String usersName, String companyName, String departmentName,
			String positionName, String address , String postCode, String tel,String email,
			String note,String share,String createusers,String createtime) {
		this.openConnection();
		int result = -1;
		if (stmnt == null)
			return result;
		// generate the query string
		String query = "INSERT INTO [card$] VALUES(";
		query += "'" + usersName + "', ";
		query += "'" + companyName + "', ";
		query += "'" + departmentName+ "', ";
		query += "'" + positionName + "', ";
		query += "'"+ address + "', ";
		query += "'"+ postCode + "', ";
		query += "'" + tel + "',";
		query += "'" + email + "',";
		query += "'" + note + "',";
		query += "'" + share + "',";
		query += "'" + createusers + "',";
		query += "'" + createtime + "'";
		query += " )";
		try {
			// execute the query
			result = stmnt.executeUpdate(query);
		} catch (SQLException e) {
			e.printStackTrace();
		}
		this.closeConnection();
		return result;
	}

	/**
	 * close the connection
	 */
	public boolean closeConnection() {
		try {
			if (stmnt != null)
				stmnt.close();
			if (c != null)
				c.close();
		} catch (Exception e) {
			System.err.println(e);
			return false;
		}
		return true;
	}
}
