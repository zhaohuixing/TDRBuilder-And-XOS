<?xml version = "1.0" ?><!-- Generated by Zhaohui Xing TDRBuilder v1.0 --><xpl version = "1.0">
<module name = "root" date = "Tue Mar 29 14:37:05 2005
">
<entry>
<input>
<variable type = "float" name = "iv1" default_value = "0.000000"/>
<variable type = "float" name = "iv2" default_value = "0.000000"/>
</input></entry><initialize>
<next id = "0"/>
<global/>
<local>
<variable type = "float" name = "lv1" default_value = "0.000000"/>


</local></initialize><processor name = "Processor" id = "0" type = "3">
<previous id = "-3"/>
<next id = "-4"/>
<method>
<![CDATA[
long Processor(void)
{
	lv1 =    5.678;
	iv1 = root(lv1, 2);
	iv2 = root(3.4+pow(2.0,2.0), 3.0);
	m_nRegister = -4;
	return m_nRegister;
}]]>
</method>

</processor></module></xpl><!-- Powered by Zhaohui Xing TDRBuilder v1.0 -->