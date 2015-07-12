package com.manager.dao.impl;

import java.util.ArrayList;
import java.util.List;

import com.manager.dao.BaseDao;
import com.manager.dao.CompanyDao;
import com.manager.entity.Company;

public class CompanyDaoImpl extends BaseDao implements CompanyDao{
	/**
	 * �������
	 */
	public int insert(Company company){
		String sql="insert into Company(CompanyName,Address,Tel,Fax) values(?,?,?,?)";
		List params=new ArrayList();
		params.add(company.getCompanyName());
		params.add(company.getAddress());
		params.add(company.getTel());
		params.add(company.getFax());
		int i=super.executeUpdate(sql, params);
		return i;
	}
	/**
	 * ɾ������
	 */
	public int delete(Company company) {
		String sql="delete from Company where CompanyId= "+company.getCompanyId();
		int i=super.executeUpdate(sql, null);
		return i;
	}
	/**
	 * �޸�����
	 */
	public int udpate(Company company) {
		String sql="update Company ";
		List params=new ArrayList();
		//�û����� Ҫ�޸��е�sql���
		String set="";
		if(company.getCompanyName() != null && !"".equals(company.getCompanyName())){
			set +=",CompanyName=?";
			params.add(company.getCompanyName());
		}
		if(company.getAddress() != null && !"".equals(company.getAddress())){
			set +=",address=?";
			params.add(company.getAddress());
		}
		if(company.getTel() != null && !"".equals(company.getTel())){
			set +=",Tel=?";
			params.add(company.getTel());
		}
		if(company.getFax() != null && !"".equals(company.getFax())){
			set +=",Fax=?";
			params.add(company.getFax());
		}
		//����ƴ�ӣ�������ɵ�sql���
		sql+=" set " +set.substring(1);
		sql+=" where CompanyId=?";
		params.add(company.getCompanyId());
		int i=super.executeUpdate(sql, params);
		return i;
	}
	/**
	 * ��ȡ����ҳ����ʾ������
	 */
	public List find(String sql1) {
		List<Company> list = super.executeQuery(sql1, null,Company.class);
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
				+ ") t where (companyid NOT IN (select top "+min+" companyid from (" + sql1+ ") t))";
		List<Company> list = super.executeQuery(sql, null,Company.class);
		return list;
	}
	/**
	 * ��ȡ��ҳ��
	 */
	public int getPageCount(int pageSize, String sql1) {
		String sql = "select count(*) companyId  from (" + sql1 + ") t";
		List<Company> list = super.executeQuery(sql, null,Company.class);
		int count = list.get(0).getCompanyId();
		int i = count % pageSize == 0 ? count / pageSize : count / pageSize + 1;
		return i;
	}
	/**
	 * ��ȡ������
	 */
	public int getTotalCount(String sql1) {
		String sql = "select count(*) companyId from (" + sql1 + ") t";
		// System.out.println(sql);
		List<Company> list = super.executeQuery(sql, null,Company.class);
		int count = list.get(0).getCompanyId();
		return count;
	}
	public int findByName(String name) {
		String sql  = "select companyId from Company where companyName='"+name+"'";
		List<Company> list = super.executeQuery(sql, null,Company.class);
		int id = list.get(0).getCompanyId();
		return id;
	}
	public String findById(int id) {
		String sql = "select * from company where companyId="+id;
		List<Company> list = super.executeQuery(sql, null,Company.class);
		return list.get(0).getCompanyName();
	}
}
