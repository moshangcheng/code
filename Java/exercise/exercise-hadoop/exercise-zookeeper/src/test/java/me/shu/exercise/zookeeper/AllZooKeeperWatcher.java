package me.shu.exercise.zookeeper;

import java.util.List;
import java.util.concurrent.CountDownLatch;
import java.util.concurrent.atomic.AtomicInteger;

import org.apache.zookeeper.CreateMode;
import org.apache.zookeeper.WatchedEvent;
import org.apache.zookeeper.Watcher;
import org.apache.zookeeper.Watcher.Event.EventType;
import org.apache.zookeeper.Watcher.Event.KeeperState;
import org.apache.zookeeper.ZooDefs.Ids;
import org.apache.zookeeper.ZooKeeper;
import org.apache.zookeeper.data.Stat;
import org.junit.Test;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

/**
 * 《ZooKeeper 事件类型详解》
 * 
 * @author nileader/nileader@gmail.com
 * 
 */
public class AllZooKeeperWatcher implements Watcher {

	private static final Logger LOG = LoggerFactory
			.getLogger(AllZooKeeperWatcher.class);

	AtomicInteger seq = new AtomicInteger();
	private static final int SESSION_TIMEOUT = 10000;
	private static final String CONNECTION_STRING = "hk-ubuntu.cloudapp.net:2181";
	private static final String ZK_PATH = "/shu/test";
	private static final String CHILDREN_PATH = "/shu/test/data";

	private ZooKeeper zk = null;

	private CountDownLatch connectedSemaphore = new CountDownLatch(1);

	/**
	 * 创建ZK连接
	 * 
	 * @param connectString
	 *            ZK服务器地址列表
	 * @param sessionTimeout
	 *            Session超时时间
	 */
	public void createConnection(String connectString, int sessionTimeout) {
		this.releaseConnection();
		try {
			zk = new ZooKeeper(connectString, sessionTimeout, this);
			LOG.info("开始连接ZK服务器");
			connectedSemaphore.await();
		} catch (Exception e) {
			e.printStackTrace();
		}
	}

	/**
	 * 关闭ZK连接
	 */
	public void releaseConnection() {
		if (this.zk != null) {
			try {
				this.zk.close();
			} catch (InterruptedException e) {
				e.printStackTrace();
			}
		}
	}

	/**
	 * 创建节点
	 * 
	 * @param path
	 *            节点path
	 * @param data
	 *            初始数据内容
	 * @return
	 */
	public boolean createPath(String path, String data) {
		try {
			this.zk.exists(path, true);
			LOG.info("节点创建成功, Path: " + this.zk.create(path, //
					data.getBytes(), //
					Ids.OPEN_ACL_UNSAFE, //
					CreateMode.PERSISTENT) + ", content: " + data);
		} catch (Exception e) {
			e.printStackTrace();
			return false;
		}
		return true;
	}

	/**
	 * 读取指定节点数据内容
	 * 
	 * @param path
	 *            节点path
	 * @return
	 */
	public String readData(String path, boolean needWatch) {
		try {
			return new String(this.zk.getData(path, needWatch, null));
		} catch (Exception e) {
			e.printStackTrace();
			return null;
		}
	}

	/**
	 * 更新指定节点数据内容
	 * 
	 * @param path
	 *            节点path
	 * @param data
	 *            数据内容
	 * @return
	 */
	public boolean writeData(String path, String data) {
		try {
			LOG.info("更新数据成功，path：" + path + ", stat: "
					+ this.zk.setData(path, data.getBytes(), -1));
		} catch (Exception e) {
			e.printStackTrace();
			return false;
		}
		return true;
	}

	/**
	 * 删除指定节点
	 * 
	 * @param path
	 *            节点path
	 */
	public void deleteNode(String path) {

		try {
			if (this.zk.exists(path, true) != null) {
				this.zk.delete(path, -1);
				LOG.info("删除节点成功，path：" + path);
			}
		} catch (Exception e) {
			e.printStackTrace();
		}
	}

	/**
	 * 删除指定节点
	 * 
	 * @param path
	 *            节点path
	 */
	public Stat exists(String path, boolean needWatch) {
		try {
			return this.zk.exists(path, needWatch);
		} catch (Exception e) {
			return null;
		}
	}

	/**
	 * 获取子节点
	 * 
	 * @param path
	 *            节点path
	 */
	private List<String> getChildren(String path, boolean needWatch) {
		try {
			return this.zk.getChildren(path, needWatch);
		} catch (Exception e) {
			return null;
		}
	}

	public void deleteAllTestPath() {
		this.deleteNode(CHILDREN_PATH);
		this.deleteNode(ZK_PATH);
	}

	@Test
	public void all() throws InterruptedException {

		AllZooKeeperWatcher sample = new AllZooKeeperWatcher();
		sample.createConnection(CONNECTION_STRING, SESSION_TIMEOUT);
		// 清理节点
		sample.deleteAllTestPath();
		if (sample.createPath(ZK_PATH, System.currentTimeMillis() + "")) {
			// 读取数据
			sample.readData(ZK_PATH, true);
			// 读取子节点
			sample.getChildren(ZK_PATH, true);

			// 更新数据
			sample.writeData(ZK_PATH, System.currentTimeMillis() + "");
			// 创建子节点
			sample.createPath(CHILDREN_PATH, System.currentTimeMillis() + "");
		}
		// 清理节点
		sample.deleteAllTestPath();
		sample.releaseConnection();
	}

	/**
	 * 收到来自Server的Watcher通知后的处理。
	 */
	@Override
	public void process(WatchedEvent event) {
		if (event == null) {
			return;
		}
		// 连接状态
		KeeperState keeperState = event.getState();
		// 事件类型
		EventType eventType = event.getType();
		// 受影响的path
		String path = event.getPath();
		String logPrefix = "【Watcher-" + this.seq.incrementAndGet() + "】";

		LOG.info(logPrefix + "收到Watcher通知");
		LOG.info(logPrefix + "连接状态:\t" + keeperState.toString());
		LOG.info(logPrefix + "事件类型:\t" + eventType.toString());

		if (KeeperState.SyncConnected == keeperState) {
			// 成功连接上ZK服务器
			if (EventType.None == eventType) {
				LOG.info(logPrefix + "成功连接上ZK服务器");
				connectedSemaphore.countDown();
			} else if (EventType.NodeCreated == eventType) {
				LOG.info(logPrefix + "节点创建");
				this.exists(path, true);
			} else if (EventType.NodeDataChanged == eventType) {
				LOG.info(logPrefix + "节点数据更新");
				LOG.info(logPrefix + "数据内容: " + this.readData(ZK_PATH, true));
			} else if (EventType.NodeChildrenChanged == eventType) {
				LOG.info(logPrefix + "子节点变更");
				LOG.info(logPrefix + "子节点列表：" + this.getChildren(ZK_PATH, true));
			} else if (EventType.NodeDeleted == eventType) {
				LOG.info(logPrefix + "节点 " + path + " 被删除");
			}

		} else if (KeeperState.Disconnected == keeperState) {
			LOG.info(logPrefix + "与ZK服务器断开连接");
		} else if (KeeperState.AuthFailed == keeperState) {
			LOG.info(logPrefix + "权限检查失败");
		} else if (KeeperState.Expired == keeperState) {
			LOG.info(logPrefix + "会话失效");
		}

		LOG.info("--------------------------------------------");

	}

}