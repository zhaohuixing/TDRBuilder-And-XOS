<?xml version = "1.0" ?><!-- /*Begin Test*/ --><xpl version = "1.0">
<module name = "cosh" date = "Tue Mar 22 16:16:12 2005
">
<entry>
<input>
<variable type = "float" name = "iv1" default_value = "0.000000e+000"/>
</input></entry><initialize>
<next id = "0"/>
<global/>
<local>
<variable type = "float" name = "lv1" default_value = "0.000000e+000"/>


</local></initialize><processor name = "Processor" id = "0" type = "3">
<previous id = "-3"/>
<next id = "-4"/>
<method>
<![CDATA[
long Processor(void)
{
	lv1 =  43.89;
	iv1 = cosh(lv1);
	m_nRegister = -4;
	return m_nRegister;
}]]>
</method>

</processor></module></xpl><!-- /*End Test*/ -->