package com.manager.dao.impl;

import java.util.ArrayList;
import java.util.List;

import com.manager.dao.BaseDao;
import com.manager.dao.PowersDao;
import com.manager.entity.Position;
import com.manager.entity.Powers;

public class PowersDaoImpl extends BaseDao implements PowersDao{
	/**
	 * �������
	 */
	public int insert(Powers power){
		String sql="insert into Powers(PowerName,UsersManager,CardManager,GroupManager,DataOut,CheckUsers,LogManager,ParameterManager,SelectGroup,AddGroup,DeleteGroup,AlterGroup,AddInGroup) values(?,?,?,?,?,?,?,?,?,?,?,?)";
		List params=new ArrayList();
		params.add(power.getUsersManager());
		params.add(power.getCardManager());
		params.add(power.getGroupManager());
		params.add(power.getDataOut());
		params.add(power.getCheckUsers());
		params.add(power.getLogManager());
		params.add(power.getParameterManager());
		params.add(power.getSelectGroup());
		params.add(power.getAddGroup());
		params.add(power.getDeleteGroup());
		params.add(power.getAlterGroup());
		params.add(power.getAddInGroup());
		int i=super.executeUpdate(sql, params);
		return i;
	}
	/**
	 * ɾ������
	 */
	public int delete(Powers power) {
		String sql="delete from Powers  where PowerId= "+power.getPowerId();
		int i=super.executeUpdate(sql, null);
		return i;
	}
	/**
	 * �޸�����
	 */
	public int udpate(Powers power) {
		String sql="update Powers  ";
		List params=new ArrayList();
		//�û����� Ҫ�޸��е�sql���
		String set="";
		if(power.getPowerName() != null && !"".equals(power.getPowerName())){
			set +=",PowerName=?";
			params.add(power.getPowerName());
		}
		if( power.getUsersManager()== 0||power.getUsersManager()== 1){
			set +=",UsersManager=?";
			params.add(power.getUsersManager());
		}
		if( power.getCardManager()== 0|| power.getCardManager()== 1){
			set +=",CardManager=?";
			params.add(power.getCardManager());
		}
		if( power.getGroupManager()== 0 ||power.getGroupManager()== 1){
			set +=",GroupManager=?";
			params.add(power.getGroupManager());
		}
		if( power.getDataOut()== 0 ||power.getDataOut()== 1){
			set +=",DataOut=?";
			params.add(power.getDataOut());
		}
		if( power.getCheckUsers()== 0||power.getCheckUsers()== 1 ){
			set +=",CheckUsers=?";
			params.add(power.getCheckUsers());
		}
		if( power.getLogManager()== 0||power.getLogManager()== 1){
			set +=",LogManager=?";
			params.add(power.getLogManager());
		}
		if( power.getParameterManager()== 0||power.getParameterManager()== 1){
			set +=",ParameterManager=?";
			params.add(power.getParameterManager());
		}
		if( power.getSelectGroup()== 0||power.getSelectGroup()== 1){
			set +=",SelectGroup=?";
			params.add(power.getSelectGroup());
		}
		if( power.getAddGroup()== 0||power.getAddGroup()== 1){
			set +=",AddGroup=?";
			params.add(power.getAddGroup());
		}
		if( power.getDeleteGroup()== 0||power.getDeleteGroup()== 1){
			set +=",DeleteGroup=?";
			params.add(power.getDeleteGroup());
		}
		if( power.getAlterGroup()== 0 ||power.getAlterGroup()== 1){
			set +=",AlterGroup=?";
			params.add(power.getAlterGroup());
		}
		if( power.getAddInGroup()== 0 ||power.getAddInGroup()== 1){
			set +=",AddInGroup=?";
			params.add(power.getAddInGroup());
		}
		//����ƴ�ӣ�������ɵ�sql���
		sql+=" set " +set.substring(1);
		sql+=" where PowerId=?";
		params.add(power.getPowerId());
		int i=super.executeUpdate(sql, params);
		return i;
	}
	/**
	 * ��ȡ����ҳ����ʾ������
	 */
	public List find(String sql1) {
		List<Powers> list = super.executeQuery(sql1, null,Powers.class);
		return list;
	}
	/**
	 * ��ȡ����ҳ����ʾ������
	 */
	public List findByPage(int pageSize, int pageNow, String sql1) {
		if(pageNow==0)
		{
			pageNow=1;
		}
		int min = (pageNow - 1) * pageSize;
		int max = pageSize * pageNow;
		String sql = "select top "+pageSize+" * from (" + sql1
				+ ") t where (powerid NOT IN (select top "+min+" powerid from (" + sql1+ ") t))";
		List<Powers> list = super.executeQuery(sql, null,Powers.class);
		return list;
	}
	/**
	 * ��ȡ��ҳ��
	 */
	public int getPageCount(int pageSize, String sql1) {
		String sql = "select count(*) powerId  from (" + sql1 + ") t";
		List<Powers> list = super.executeQuery(sql, null,Powers.class);
		int count = list.get(0).getPowerId();
		int i = count % pageSize == 0 ? count / pageSize : count / pageSize + 1;
		return i;
	}
	/**
	 * ��ȡ������
	 */
	public int getTotalCount(String sql1) {
		String sql = "select count(*) powerId from (" + sql1 + ") t";
		// System.out.println(sql);
		List<Powers> list = super.executeQuery(sql, null,Powers.class);
		int count = list.get(0).getPowerId();
		return count;
	}
	public String findById(int id) {
		String sql = "select * from powers where powerId="+id;
		List<Powers> list = super.executeQuery(sql, null,Powers.class);
		return list.get(0).getPowerName();
	}
}
