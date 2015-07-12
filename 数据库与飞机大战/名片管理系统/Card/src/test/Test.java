package test;

import java.sql.Connection;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.text.DateFormat;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.Date;

import com.manager.dao.DBConnection;

public class Test {

	/**
	 * @param args
	 * @throws ParseException 
	 */
	public static void main(String[] args) throws ParseException {
		/*try {
			Connection conn=DBConnection.getConnection();
			Statement stmt=conn.createStatement();
			ResultSet rst = stmt.executeQuery("select * from Users");
			while(rst.next())
			{
				System.out.println(rst.getString(3));
			}
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}*/
		/*DateFormat fmt =new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");    
		String s = "1993-01-01 01:01:01.0";
        Date date = fmt.parse(s);
        System.out.println(fmt.format(date));
        System.out.println(date.getTime());
        java.sql.Date d = java.sql.Date.valueOf(s);
        System.out.println(d);*/
		Date d = new Date();
		SimpleDateFormat sdf = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");
		try {
			String now = sdf.format(d);
			d = sdf.parse(now);
			System.out.println(d);
		} catch (ParseException e) {
			e.printStackTrace();
		}
	}

}
