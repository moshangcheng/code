package me.shu.exercise.hive;

import static org.junit.Assert.*;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;

import org.junit.Test;

/**
 * To run this test, start hiveserver2 first
 * @see <a
 *      href="https://cwiki.apache.org/confluence/display/Hive/HiveServer2+Clients">hive
 *      client doc</a>
 * @author moshangcheng
 *
 */
public class HiveJdbcClientTest {

	private static String driverName = "org.apache.hive.jdbc.HiveDriver";

	@Test
	public void connectTest() {
		try {
			Class.forName(driverName);
		} catch (ClassNotFoundException e) {
			e.printStackTrace();
			assertFalse(true);
		}
		try {
			Connection con = DriverManager.getConnection(
					"jdbc:hive2://hk-ubuntu.cloudapp.net:10000/shu_db", "", "");
		} catch (SQLException e) {
			e.printStackTrace();
			assertFalse(true);
		}
	}
}
