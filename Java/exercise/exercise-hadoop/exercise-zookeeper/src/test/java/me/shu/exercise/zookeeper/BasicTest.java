package me.shu.exercise.zookeeper;

import static org.junit.Assert.*;

import java.io.IOException;

import org.apache.zookeeper.KeeperException;
import org.apache.zookeeper.ZooKeeper;
import org.junit.Test;

public class BasicTest {

	private static final String HOST_NAME = "hk-ubuntu.cloudapp.net";
	private static final String ZNODE_PATH = "/shu/test/data";
	private static final String ZNODE_DATA = "data-for-test";

	@Test
	public void connectTest() {
		try {
			ZooKeeper zk = new ZooKeeper(HOST_NAME, 10000, null);
			assertNotNull(zk);
			assertTrue(zk.getState().isAlive());
		} catch (IOException e) {
			assertFalse(true);
		}
		assertTrue(true);
	}

	@Test
	public void getTest() {
		try {
			ZooKeeper zk = new ZooKeeper(HOST_NAME, 10000, null);

			assertNotNull(zk);
			assertTrue(zk.getState().isAlive());

			byte[] data = zk.getData(ZNODE_PATH, false, null);

			assertNotNull(data);
			assertTrue(ZNODE_DATA.equals(new String(data)));

		} catch (IOException | KeeperException | InterruptedException e) {
			assertFalse(true);
		}
		assertTrue(true);
	}
}
