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

public class GroupExcelAccess {
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
	public GroupExcelAccess() {
		driver = "sun.jdbc.odbc.JdbcOdbcDriver";
		url = "jdbc:odbc:group";
		username = "";
		password = "";
	}

	/**
	 * constructor with specified parameters
	 */
	public GroupExcelAccess(String driver, String url, String username,
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
	public int insertEmpInfo(String groupName, String fatherGroupName, String usersName,
			String createtime, String companyName, String departmentName,
			String note,String share) {
		this.openConnection();
		int result = -1;
		if (stmnt == null)
			return result;
		// generate the query string
		String query = "INSERT INTO [group$] VALUES(";
		query += "'" + groupName + "', ";
		query += "'" + fatherGroupName + "', ";
		query += "'" + usersName + "', ";
		query += "'" + createtime + "', ";
		query += "'"+ companyName + "', ";
		query += "'" + departmentName + "',";
		query += "'" + note + "',";
		query += "'" + share + "'";
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
