<?xml version = "1.0" ?><!-- Generated by Zhaohui Xing TDRBuilder v1.0 --><xpl version = "1.0">
<module name = "log10" date = "Tue Mar 29 14:31:09 2005
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
	iv1 = log10(lv1);
	iv2 = log10(3.4+pow(2.0,2.0));
	m_nRegister = -4;
	return m_nRegister;
}]]>
</method>

</processor></module></xpl><!-- Powered by Zhaohui Xing TDRBuilder v1.0 -->