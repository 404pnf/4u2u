function getreturn(){
	username = document.getElementById('edit-name').value;
	userpass = document.getElementById('edit-pass').value;
	document.getElementById('edit-userpass').value = f23.s52e(username+'(!@#$%&*)'+userpass);      
}

function register_getreturn(){
	username = document.getElementById('edit-name').value;
	userpass = document.getElementById('edit-pass-pass1').value;
	document.getElementById('edit-userpass').value = f23.s52e(username+'(!@#$%&*)'+userpass);
}

f23={}
f23.ts="8ABC7DLO5MN6Z9EFGdeJfghijkHIVrstuvwWSTUXYabclmnopqKPQRxyz01234"
f23.s52e=function(n)
{
	var nl=n.length,t=[],a,b,c,x,m=function(y){t[t.length]=f23.ts.charAt(y)},N=f23.ts.length,N2=N*N,N5=N*5
	for(x=0;x<nl;x++)
	{
		a=n.charCodeAt(x)
		if(a<N5)m(Math.floor(a/N)),m(a%N)
		else m(Math.floor(a/N2)+5),m(Math.floor(a/N)%N),m(a%N)
	}
	var s=t.join("")
	return String(s.length).length+String(s.length)+s
}

f23.s52d=function(n)
{
	var c=n.charAt(0)*1
	if(isNaN(c))return ""
	c=n.substr(1,c)*1
	if(isNaN(c))return ""
	var nl=n.length,t=[],a,f,b,x=String(c).length+1,m=function(y){return f23.ts.indexOf(n.charAt(y))},N=f23.ts.length
	if(nl!=x+c)return ""
	while(x<nl)
	{
		a=m(x++)
		if(a<5)f=a*N+m(x)
		else f=(a-5)*N*N+m(x)*N+m(x+=1)
		t[t.length]=String.fromCharCode(f)
		x++
	}
	return t.join("")
}
