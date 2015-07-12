package com.user.dao.impl;

import java.util.ArrayList;
import java.util.List;

import com.manager.dao.BaseDao;
import com.manager.dao.impl.CompanyDaoImpl;
import com.manager.entity.Card_Users;
import com.user.dao.Card_UsersDao;

public class Card_UsersDaoImpl extends BaseDao implements Card_UsersDao{
	/**
	 * 获取给定页，显示的数据
	 */
	public List find(String sql1) {
		List<Card_Users> list = super.executeQuery(sql1, null,Card_Users.class);
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
		List<Card_Users> list = super.executeQuery(sql, null,Card_Users.class);
		return list;
	}
	/**
	 * 获取总页数
	 */
	public int getPageCount(int pageSize, String sql1) {
		String sql = "select count(*) cardId  from (" + sql1 + ") t";
		List<Card_Users> list = super.executeQuery(sql, null,Card_Users.class);
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
		List<Card_Users> list = super.executeQuery(sql, null,Card_Users.class);
		int count = list.get(0).getCardId();
		return count;
	}
	public int delete(Card_Users cu) {
		// TODO Auto-generated method stub
		String sql="delete from Card_Users  where cardId= "+cu.getCardId();
		int i=super.executeUpdate(sql, null);
		return i;
	}
	public int insert(Card_Users cu) {
		// TODO Auto-generated method stub
		String sql = "update card_users ";
		List params = new ArrayList();
		String set = "";
		if(cu.getAddress()!=null&&!"".equals(cu.getAddress())){
			set+=",address=?";
			params.add(cu.getAddress());
		}
		if(cu.getCardUsersName()!=null&&!"".equals(cu.getCardUsersName())){
			set+=",cardusersname=?";
			params.add(cu.getCardUsersName());
		}
		if(cu.getPostCode()!=0&&!"".equals(cu.getPostCode())){
			set+=",postcode=?";
			params.add(cu.getPostCode());
		}
		if(cu.getEmail()!=null&&!"".equals(cu.getEmail())){
			set+=",email=?";
			params.add(cu.getEmail());
		}
		if(cu.getTel()!=null&&!"".equals(cu.getTel())){
			set+=",tel=?";
			params.add(cu.getTel());
		}
		if(cu.getCompanyId()!=0){
			set+=",companyid=?";
			params.add(cu.getCompanyId());
		}
		if(cu.getDepartmentId()!=0){
			set+=",departmentid=?";
			params.add(cu.getDepartmentId());
		}
		if(cu.getPositionId()!=0){
			set+=",positionid=?";
			params.add(cu.getPositionId());
		}
		sql+=" set " +set.substring(1);
		sql+=" where cardid=?";
		params.add(cu.getCardId());
		int i=super.executeUpdate(sql, params);
		return i;
		
	}
	public int update(Card_Users cu) {
		// TODO Auto-generated method stub
		return 0;
	}
	public Card_Users findById(int id) {
		String sql = "select * from Card_Users where CardId="+id;
		List<Card_Users> list = super.executeQuery(sql, null,Card_Users.class);
		return list.get(0);
	}
}
