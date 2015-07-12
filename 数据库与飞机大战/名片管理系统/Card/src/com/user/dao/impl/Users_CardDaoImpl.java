package com.user.dao.impl;

import java.util.ArrayList;
import java.util.List;

import com.manager.dao.BaseDao;
import com.manager.entity.Users_Card;
import com.user.dao.Users_CardDao;

public class Users_CardDaoImpl extends BaseDao implements Users_CardDao{
	/**
	 * 获取给定页，显示的数据
	 */
	public List find(String sql1) {
		List<Users_Card> list = super.executeQuery(sql1, null,Users_Card.class);
		return list;
	}
	/**
	 * 获取给定页，显示的数据
	 */
	public List findByPage(int pageSize, int pageNow, String sql1) {
		if(pageNow==0)
		{
			pageNow=1;
		}
		int min = (pageNow - 1) * pageSize;
		int max = pageSize * pageNow;
		String sql = "select top "+pageSize+" * from (" + sql1
				+ ") t where (CardId NOT IN (select top "+min+" CardId from (" + sql1+ ") t))";
		List<Users_Card> list = super.executeQuery(sql, null,Users_Card.class);
		return list;
	}
	/**
	 * 获取总页数
	 */
	public int getPageCount(int pageSize, String sql1) {
		String sql = "select count(*) cardId  from (" + sql1 + ") t";
		List<Users_Card> list = super.executeQuery(sql, null,Users_Card.class);
		int count = list.get(0).getCardId();
		int i = count % pageSize == 0 ? count / pageSize : count / pageSize + 1;
		return i;
	}
	/**
	 * 获取总条数
	 */
	public int getTotalCount(String sql1) {
		String sql = "select count(*) cardId from (" + sql1 + ") t";
		// System.out.println(sql);
		List<Users_Card> list = super.executeQuery(sql, null,Users_Card.class);
		int count = list.get(0).getCardId();
		return count;
	}
	public int delete(Users_Card uc) {
		// TODO Auto-generated method stub
		String sql="delete from Users_Card  where cardId= "+uc.getCardId();
		int i=super.executeUpdate(sql, null);
		return i;
	}
	public int insert(Users_Card uc) {
		// TODO Auto-generated method stub
		return 0;
	}
	public int update(Users_Card uc) {
		// TODO Auto-generated method stub
		
		return 0;
	}
	public int findByCardId(int id) {
		String sql = "select * from users_card where cardId="+id;
		List<Users_Card> list = super.executeQuery(sql, null,Users_Card.class);
		return list.get(0).getUsersId();
	}
}
