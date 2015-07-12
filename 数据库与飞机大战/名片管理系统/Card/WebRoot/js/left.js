// JavaScript Document
function Users()
{
   document.getElementById("users").style.display='block';
   document.getElementById("manager").style.display='none';
   document.getElementById("log").style.display='none';
}
function Manager()
{
   document.getElementById("manager").style.display='block';
   document.getElementById("users").style.display='none';
   document.getElementById("log").style.display='none';
}
function Log()
{
   document.getElementById("log").style.display='block';
   document.getElementById("manager").style.display='none';
   document.getElementById("users").style.display='none';
}
function select_all(){ //全选     
    var inputs = document.getElementsByTagName("input");     
    for(var i=0;i<inputs.length;i++)     
    {     
      if(inputs[i].getAttribute("name") == "success")     
      {     
        inputs[i].checked = true;     
      } 
      if(inputs[i].getAttribute("name") == "failure")     
      {     
        inputs[i].checked = false;     
      } 
      if(inputs[i].getAttribute("name") == "checkboxno")     
      {     
        inputs[i].checked = false;     
      }
    }     
  }   
function select_no(){ //全不选     
    var inputs = document.getElementsByTagName("input");     
    for(var i=0;i<inputs.length;i++)     
    {     
      if(inputs[i].getAttribute("name") == "failure")     
      {     
        inputs[i].checked = true;     
      } 
      if(inputs[i].getAttribute("name") == "success")     
      {     
        inputs[i].checked = false;     
      } 
      if(inputs[i].getAttribute("name") == "checkboxall")     
      {     
        inputs[i].checked = false;     
      } 
    }     
  }   
function CheckSuccess()
{
	document.getElementById("formregister").action = "AddUserServlet.action";
	document.formregister.submit();
}
function CheckFail()
{
	document.getElementById("formregister").action = "DeleteRegister.action";
	document.formregister.submit();
}
function SetNum()
{
	var num = document.getElementById("pageSize").value;
	if(num>0)
	{
		window.location.href="RegisterSelectAllServlet.action?pageNow=1&&pageSize="+num;
	}
}
function Jump()
{
	var num = document.getElementById("jump").value;
	if(num>0)
	{
		window.location.href="RegisterSelectAllServlet.action?pageNow="+num;
	}
}