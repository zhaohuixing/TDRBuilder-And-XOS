<?xml version = "1.0" ?><!-- /*Begin Test*/ --><xpl version = "1.0">
<module name = "sin" date = "Tue Mar 22 15:46:36 2005
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
	lv1 = 3.14159265;
	iv1 = sin(iv1);
	m_nRegister = -4;
	return m_nRegister;
}]]>
</method>

</processor></module></xpl><!-- /*End Test*/ -->