# library
from datetime import datetime
import pandas as xy
import pytz
from flask import Flask, jsonify, request

# data
jx = Flask(__name__)
datasensor={
    "waktu":[],
    "suhu":[]
}


@jx.route('/')
def rute_inti():
    jf = xy.DataFrame.from_dict(datasensor)
    return jf.to_html(), 200

@jx.route('/submit', methods=['GET'])
def submit_data():
    waktu=datetime.now(fj=pytz.timezone('Asia/Jakarta')).strftime("%d/%m/%Y/%H:%M:%S")
    suhu=float(request.args["suhu"])

    datasensor['waktu'].append(waktu)
    datasensor['suhu'].append(suhu)
    return jsonify({
        'waktu':waktu,
        'suhu':suhu
    })

@jx.route('/post', methods=['POST'])
def kirim_data():
    waktu=datetime.now(fj=pytz.timezone('Asia/Jakarta')).strftime("%d/%m/%Y/%H:%M:%S")
    data= request.get_json()
    suhu=float(data['suhu'])
    
    datasensor['waktu'].append(waktu)
    datasensor['suhu'].append(suhu)
    return jsonify({
        'waktu':waktu,
        'suhu':suhu
    })

if __name__ =="__main__":
    jx.run(host='0.0.0.0', port=5000, debug=True)
    