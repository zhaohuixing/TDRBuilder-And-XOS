<?xml version = "1.0" ?><!-- Generated by Zhaohui Xing TDRBuilder v1.0 --><xpl version = "1.0">
<module name = "exp" date = "Tue Mar 29 13:22:20 2005
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
	lv1 = 0.67845;
	iv1 = exp(lv1);
	iv2 = exp(3.0+3.5*2.0);
	m_nRegister = -4;
	return m_nRegister;
}]]>
</method>

</processor></module></xpl><!-- Powered by Zhaohui Xing TDRBuilder v1.0 -->